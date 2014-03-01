#include<stdio.h>
#include<time.h>
struct Heap {
    int v;
}Heap[10000001];/*max heap*/
int L;
void Swap(int P, int S) {
    int T;
    T=Heap[P].v, Heap[P].v=Heap[S].v, Heap[S].v=T;
}
void siftup (int site) {
    int S = site, P = site >> 1;
    while(S >= 2 && Heap[P].v > Heap[S].v)
        Swap(P, S), S = P, P = S >> 1;
}
void siftdown(int site) {
    int P = site, S = site << 1;
    while(S <= L) {
        if(S < L && Heap[S+1].v < Heap[S].v)    S++;
        if(Heap[P].v <= Heap[S].v)    break;
        Swap(P, S), P = S, S = P << 1;
    }
}
void insHeap(int site, int t) {/*insert new node*/
    Heap[site].v = t;
    siftup(site);
}
void delHeap() {/*delete last node*/
    Swap(1, L), L--;
    siftdown(1);
} 
main() {
	freopen("in1.txt", "rt", stdin);   
	freopen("out1.txt", "w+t", stdout);
    clock_t st, ed;
    st = clock();
	L = 0;
	int n;
	while(scanf("%d", &n) == 1)
		L++, insHeap(L, n);


	while(L) {
		printf("%d ", Heap[1].v);
		delHeap();
	}
	puts("");	
	ed = clock();
	printf("%f\n", (float)(ed - st)/CLOCKS_PER_SEC);
	return 0;
}
