#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "FibonacciHeap.h"

int compar(int a, int b) {
	return a-b;
}

int main() {
	srand(time(NULL));
	int a;
	
	FibonacciHeap<int> *fh = new FibonacciHeap<int>(compar);
	
	for (int i=0; i<2; i++) {
		for (int j=0; j<4; j++) {
			a = rand()%100;
			printf("inserting %d\n",a);
			fh->push(a);
		}
	
		for (int j=0; j<2; j++) {
			printf("pop's return: %d\n",fh->pop());
		}
		printf("\nthe fibonacci heap has %d elements\n",fh->size());
		printf("element in the top: %d\n\n",fh->top());
	}
	
	fh->reset();

	return 0;
}
