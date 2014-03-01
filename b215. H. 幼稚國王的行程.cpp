#include<stdio.h>
#define MaxV 1000000
int Input();
void MergeSort(int, int);
void Merge(int, int, int);
/*mapped-heap begin*/
struct Heap {
    short x, node;
}Heap[1001];/*min heap*/
int L, set[1001];
char exist[1001];
void Swap(int P, int S) {
    int T;
    T=Heap[P].x, Heap[P].x=Heap[S].x, Heap[S].x=T;
    T=Heap[P].node, Heap[P].node=Heap[S].node, Heap[S].node=T;
    set[Heap[S].node] = S, set[Heap[P].node] = P;
}
void siftup (int site) {
    int S = site, P = site >> 1;
    while(S >= 2 && Heap[P].x > Heap[S].x)
        Swap(P, S), S = P, P = S >> 1;
}
void siftdown(int site) {
    int P = site, S = site << 1;
    while(S <= L) {
        if(S < L && Heap[S+1].x < Heap[S].x)    S++;
        if(Heap[P].x <= Heap[S].x)    break;
        Swap(P, S), P = S, S = P << 1;
    }
}
void insHeap(int site, int node, int t) {/*insert new node*/
    Heap[site].node = node;
    Heap[site].x = t;
    set[node] = site, exist[node] = 1;
    siftup(site);
}
void delHeap() {/*delete last node*/
    exist[Heap[1].node] = 0;
    Swap(1, L), L--;
    siftdown(1);
}
void modHeap(int site, int t) {/*modify old node*/
    Heap[site].x = t;
    siftup(site);
}
/*mapped-heap end*/
struct Link {
	short x, y, w;
}Data[1000001], X[1000001];
int NodeT[1001], NodeL[1001], D[1001];
char V[1001];
int Dijkstra(int st, int ed, int N, int Dis) {
	int a, b, c, tn;
	for(a = 1, L = 0; a <= N; a++)
		D[a] = MaxV, V[a] = 0, exist[a] = 0;
	for(a = 0, b = NodeL[st], c = NodeT[st]; a < c; a++, b++)
		if(Data[b].w < D[Data[b].y]) {
			D[Data[b].y] = Data[b].w;
			if(exist[Data[b].y])
				modHeap(set[Data[b].y], D[Data[b].y]); 
			else {
				++L, insHeap(L, Data[b].y, D[Data[b].y]);
			}
		}
	L++, insHeap(L, st, MaxV);
	while(1) {
		tn = Heap[1].node, V[tn] = 1;
		if(L < 1 || D[tn] > Dis)	break;
		for(a = 0, b = NodeL[tn], c = NodeT[tn]; a < c; a++, b++) {
			if(V[Data[b].y] == 0 && D[tn] + Data[b].w < D[Data[b].y]) {
				D[Data[b].y] = D[tn] + Data[b].w;
				if(exist[Data[b].y])
					modHeap(set[Data[b].y], D[Data[b].y]);
				else {
					++L, insHeap(L, Data[b].y, D[Data[b].y]);
				}
			}
		}
		if(D[ed] <= Dis)	return 1;
		delHeap();
	}
	return 0;
}
main() {
    int t, n, m, d, x, y, w, a, T;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &d);
        for(a = 1; a <= n; a++)/*init*/
        	NodeT[a] = 0, NodeL[a] = MaxV;
        	
        for(a = 0, T = 0; a < m; a++) {
			x = Input(), y = Input(), w = Input();
			if(x == y) continue;
			Data[T].x = x, Data[T].y = y, Data[T].w = w;
			NodeT[x]++, T++;
		}
		MergeSort(0, T-1);
		for(a = 0; a < T; a++)
			NodeL[Data[a].x] = NodeL[Data[a].x] < a ? NodeL[Data[a].x]: a;
		int Ans[1001], At = 0;
		for(a = 1; a <= n; a++) {
			if(Dijkstra(a, a, n, d)) 
				Ans[At++] = a;
		}
		printf("%d\n", At);
		for(a = 0; a < At; a++)
			printf("%d ", Ans[a]);
		puts("");
    }
    return 0;
}
void MergeSort(int l, int h) {
	if(l < h) {
		int m = (l+h)/2;
		MergeSort(l, m);
		MergeSort(m+1, h);
		Merge(l, m, h);
	}
}
void Merge(int l, int m, int h) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= h) {
		if(Data[In1].x < Data[In2].x || (Data[In1].x == Data[In2].x && Data[In1].w <= Data[In2].w))
			X[Top++] = Data[In1++];
		else
			X[Top++] = Data[In2++];
	}
	while(In1 <= m) X[Top++] = Data[In1++];
	while(In2 <= h)	X[Top++] = Data[In2++];
	for(a = 0, b = l; a < Top; a++, b++)
		Data[b] = X[a];
}
int Input() {
    char cha;
    unsigned int x = 0;
    while(cha = getchar())
        if(cha != ' ' && cha != '\n') break;
    x = cha-48;
    while(cha = getchar()) {
        if(cha == ' ' || cha == '\n') break;
        x = x*10 + cha-48;
    }
    return x;
}
