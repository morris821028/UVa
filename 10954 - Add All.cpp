#include<stdio.h>
int Heap[5001], L;
void Swap(int x, int y) {
	static int tmp;
	tmp = Heap[x], Heap[x] = Heap[y], Heap[y] = tmp;
}
int siftUp(int site) {
	static int P, S;
	S = site, P = site>>1;
	while(S >= 2 && Heap[P] > Heap[S])
		Swap(P, S), S = P, P = S>>1;
}
int siftDown(int site) {
	static int P, S;
	P = site, S = site<<1;
	while(S <= L) {
		if(S < L && Heap[S+1] < Heap[S])
			S++;
		if(Heap[S] >= Heap[P])
			break;
		Swap(P, S), P = S, S = P<<1;
	}
}
void insHeap(int v) {
	++L;
	Heap[L] = v;
	siftUp(L);
}
void delHeap() {
	Swap(1, L), L--;
	siftDown(1);
}
int main() {
	int N, i, v;
	while(scanf("%d", &N) == 1 && N) {
		L = 0;
		for(i = 0; i < N; i++) {
			scanf("%d", &v);
			insHeap(v);
		}
		int x, y, sum = 0;
		while(L >= 2) {
			x = Heap[1];
			delHeap();
			y = Heap[1];
			delHeap();
			sum += x+y;
			insHeap(x+y);
		}
		printf("%d\n", sum);
	}
    return 0;
}
