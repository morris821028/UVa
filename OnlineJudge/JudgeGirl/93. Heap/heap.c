#include "heap.h"

#define swap(x, y) {int t; t = x, x = y, y = t;}
static void pushup(struct Heap *heap, int x) {
	int S = x, P = x>>1;
    while (S >= 2 && heap->A[P] > heap->A[S]) {
    	swap(heap->A[P], heap->A[S]);
        S = P, P = S>>1;
    }
}
static void pushdown(struct Heap *heap, int x) {
	int P = x, S = x<<1;
    while (S <= heap->n) {
        if (S < heap->n && heap->A[S+1] < heap->A[S])
			S++;
        if (heap->A[P] <= heap->A[S])
			break;
        swap(heap->A[P], heap->A[S]);
		P = S, S = P<<1;
    }
}
void initialize(struct Heap *heap) {
    heap->n = 0;
}
int removeMin(struct Heap *heap) {
    int mn = heap->A[1];
    heap->A[1] = heap->A[heap->n];
    (heap->n)--;
    pushdown(heap, 1);
    return mn;
}
void add(struct Heap *heap, int i) {
    (heap->n)++;
    heap->A[heap->n] = i;
    pushup(heap, heap->n);
}
int isFull(struct Heap *heap) {
    return heap->n == MAXHEAP;
}
int isEmpty(struct Heap *heap) {
    return heap->n == 0;
}
