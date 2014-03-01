#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "node.h"

class Heap {
	private:
        static const int SIZE = 16385;

		int cnt;
		Node tree[SIZE];

        int cmp(int, int);
	public:
		Heap();

		bool isEmpty();
		int getCnt();
		void insert(Node);
		Node remove();
		void print();
};

#endif // HEAP_H_INCLUDED
