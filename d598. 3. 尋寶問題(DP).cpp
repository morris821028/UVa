#include<stdio.h>
#include<string.h>
#define oo 40000
int Trea[21], n, m;
int map[21][21], F[21][21];
struct Heap {
    int hv, v, status;
    char find, last;
}Heap[2000000];/*min heap*/
int L;
void Floyd() {
	int a, b, c;
	for(a = 1; a <= n; a++) {
		for(b = 1; b <= n; b++) {
			F[a][b] = map[a][b];
			if(F[a][b] == 0)	F[a][b] = oo;
			if(a == b) F[a][b] = 0;
		}
	}
	for(a = 1; a <= n; a++)
		for(b = 1; b <= n; b++)
			for(c = 1; c <= n; c++)
				if(F[b][a]+F[a][c] < F[b][c])
					F[b][c] = F[b][a]+F[a][c];
}
void Swap(int P, int S) {
    int T;
    T = Heap[P].hv, Heap[P].hv = Heap[S].hv, Heap[S].hv = T;
	T = Heap[P].v, Heap[P].v = Heap[S].v, Heap[S].v = T;
    T = Heap[P].status, Heap[P].status = Heap[S].status, Heap[S].status = T;
    T = Heap[P].last, Heap[P].last = Heap[S].last, Heap[S].last = T;
    T = Heap[P].find, Heap[P].find = Heap[S].find, Heap[S].find = T;
}
void siftup (int site) {
    int S = site, P = site >> 1;
    while(S >= 2 && Heap[P].hv > Heap[S].hv)
        Swap(P, S), S = P, P = S >> 1;
}
void siftdown(int site) {
    int P = site, S = site << 1;
    while(S <= L) {
        if(S < L && Heap[S+1].hv < Heap[S].hv)    S++;
        if(Heap[P].hv <= Heap[S].hv)    break;
        Swap(P, S), P = S, S = P << 1;
    }
}
void insHeap(int site, int hv, int v, int last, int find, int status) {/*insert new node*/
	Heap[site].hv = hv;
    Heap[site].v = v;
	Heap[site].last = last;
    Heap[site].find = find;
	Heap[site].status = status;
    siftup(site);
}
void delHeap() {/*delete last node*/
    Swap(1, L), L--;
    siftdown(1);
}
int H(int now, int find) {
    return F[now][n]+(m-find-1);
}
main() {
	while(scanf("%d %d", &n, &m) == 2) {
		int a, b, find = 0, x;
		for(a = 0; a < m; a++)
			scanf("%d", &Trea[a]);
		for(a = 1; a <= n; a++)
			for(b = 1; b <= n; b++)
				scanf("%d", &map[a][b]);
		Floyd(), L = 0;
		for(a = 0; a < m; a++) {
			L++, insHeap(L, F[1][Trea[a]]+H(Trea[a], 1), F[1][Trea[a]], a, 1, 1<<a);
		}
		int final = (1 << m)-1;
		int status, status_v, status_last, status_find;
		int tmp_status, tmp_status_v, Ans = -1;
		while(L) {
			status = Heap[1].status, status_v = Heap[1].v;
			status_last = Heap[1].last, status_find = Heap[1].find;
			if(status == final) {
				Ans = status_v + F[Trea[status_last]][n];break;
			}
			delHeap();
			for(b = 0; b < m; b++) {
				if((status & (1<<b)) == 0) {
					tmp_status = status | (1<<b);
					tmp_status_v = status_v + F[Trea[status_last]][Trea[b]];
					L++, insHeap(L, tmp_status_v+H(Trea[b], status_find+1), tmp_status_v, b, status_find+1, tmp_status);
				}
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
