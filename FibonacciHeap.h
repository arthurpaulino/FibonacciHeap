#ifndef H_FIBONACCIHEAP
#define H_FIBONACCIHEAP

#include <cmath>

template <class T>
class FibonacciHeap {

private:
	
	class Node {
		public:
			T conteudo;
			int grau;
			bool isroot, mark;
			Node *pai, *ant, *prox, *filho;
			Node():grau(0),isroot(0),mark(0),pai(0),ant(0),prox(0),filho(0){}
	};

	Node *H, *menor;
	int nElements;
	int (*f)(T, T);
		
	void lista_vira_raiz(Node *l) {
		if (l!=0) {
			Node *aux = H;
			while (aux->prox != 0) aux = aux->prox;
			aux->prox = l;
			l->ant = aux;
			aux = l;
			while (l != 0) {
				l->isroot = true;
				l->mark = false;
				l->pai = 0;
				l = l->prox;
			}
		}
	}

	void set_menor() {
		menor = H;
		Node *aux = H;
		while (aux != 0)	{
			if (f(aux->conteudo,menor->conteudo) < 0) menor = aux;
			aux = aux->prox;
		}	
	}

	Node *link(Node *a, Node *b) {
		Node *maior_no, *menor_no;
		if (f(a->conteudo,b->conteudo) > 0) {
			maior_no = a;
			menor_no = b;
		}
		else {
			maior_no = b;
			menor_no = a;
		}
		maior_no->isroot = false;
		menor_no->grau++;
		if (H == maior_no) H = maior_no->prox;
		if (maior_no->ant != 0) maior_no->ant->prox = maior_no->prox;
		if (maior_no->prox != 0) maior_no->prox->ant = maior_no->ant;
		maior_no->ant = 0;
		maior_no->prox = menor_no->filho;
		if (menor_no->filho != 0) menor_no->filho->ant = maior_no;
		menor_no->filho = maior_no;
		maior_no->pai = menor_no;
		return menor_no;
	}

	Node *proximo(Node **A, int tam, int posicao) {
		for (posicao; posicao<tam; posicao++) {
			if (A[posicao] != 0) return A[posicao];
		}
		return 0;
	}

	Node *anterior(Node **A, int tam, int posicao) {
		for (posicao; posicao>=0; posicao--) {
			if (A[posicao] != 0) return A[posicao];
		}
		return 0;
	}

	void consolida() {
		int M = 2 + (int)(log2(nElements));
		Node *A[M], *aux = H, *proximo_da_lista, *r;
		int i,d;
		for (i=0;i<M;i++) A[i] = 0;
		while (aux != 0) {
			proximo_da_lista = aux->prox;
			r = aux;
			d = r->grau;
			while (A[d] != 0) {
				r = link(r,A[d]);
				A[d] = 0;
				d++;
				if (d>=M) break;
			}
			A[d] = r;
			aux = proximo_da_lista;
		}
		H = 0;
		for (i=0;i<M;i++) {
			if (A[i] != 0) {
				H = A[i];
				d = i;
				break;
			}
		}
		for (i=d;i<M;i++) {
			if (A[i] != 0) {
				A[i]->prox = proximo(A,M,i+1);
				A[i]->ant = anterior(A,M,i-1);
			}
		}
	}

	void no_vira_raiz(Node **H, Node *l) {
		Node *pai = l->pai;
		pai->grau--;
		if (l->ant != 0) l->ant->prox = l->prox;
		if (l->prox != 0) l->prox->ant = l->ant;
		if (pai->filho == l) pai->filho = l->prox;
		l->ant = 0;
		l->prox = *H;
		l->pai = 0;
		l->isroot = true;
		l->mark = false;
		(*H)->ant = l;
		*H = l;
		if (pai->isroot == false) {
			if (pai->mark == false) {
				pai->mark = true;			
			} else {
				no_vira_raiz(H, pai);
			}
		}
	}

	void clear_recursivo(Node *node) {
		if (node != 0) {
			clear_recursivo(node->prox);
			clear_recursivo(node->filho);
			delete node;
		}
	}
		
public:
	
	FibonacciHeap(int (*f)(T, T)):H(0),menor(0),nElements(0),f(f){}

	int size() {return nElements;}

	T top() {return menor->conteudo;}

	void push(T conteudo) {
		Node *aux = new Node();
		aux->conteudo = conteudo;
		aux->grau = 0;
		aux->isroot = true;
		if (H==0) {
			H = aux;
			menor = aux;
		} else {
			aux->prox = H;
			H->ant = aux;
			H = aux;
			if (f(aux->conteudo,menor->conteudo) < 0) menor = aux;
		}
		nElements++;
	}

	T pop() {
		if (H == 0) return 0;
		T retorno = menor->conteudo;
		if (menor->ant != 0) menor->ant->prox = menor->prox;
		if (menor->prox != 0) menor->prox->ant = menor->ant;
		lista_vira_raiz(menor->filho);
		if (H == menor) H = menor->prox;
		delete menor;
		nElements--;
		if (nElements>0) {
			consolida();
			set_menor();
		}
		return retorno;
	}

	void reset() {
		clear_recursivo(H);
		H = 0;
		menor = 0;
		nElements = 0;
	}
	
	virtual ~FibonacciHeap() {
		clear_recursivo(H);
	}
};

#endif
