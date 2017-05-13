#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "FibonacciHeap.h"

int compara(int a, int b) {
	return a-b;
}

int main() {
	srand(time(NULL));
	int a;
	
	FibonacciHeap<int> *fh = new FibonacciHeap<int>(compara);
	
	for (int i=0; i<2; i++) {
		for (int j=0; j<4; j++) {
			a = rand()%100;
			printf("inserindo %d\n",a);
			fh->push(a);
		}
	
		for (int j=0; j<2; j++) {
			printf("%d removido\n",fh->pop());
		}
		printf("\n%d elementos no heap\n",fh->size());
		printf("top: %d\n\n",fh->top());
	}
	
	fh->reset();

	return 0;
}
