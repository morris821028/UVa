#include<stdio.h>
#define MaxV 100000000
#define MaxN 1001
#define MaxK 1001
#define MaxM 100000
typedef struct Link {
    int x, y, w;
}Link;
struct Heap {
	int v, node;
}Heap[MaxN*MaxK];/*min heap*/
int L;
void Swap(int, int);
void siftup(int);
void siftdown(int);
void insHeap(int, int, int);
void delHeap();
void MergeSort(int, int, Link[]);
void Merge(int, int, int, Link[]);

Link Data[MaxM], X[MaxM], RevD[MaxM];
int NodeT[MaxN], NodeL[MaxN];
int RevNT[MaxN], RevNL[MaxN];
int Hdis[MaxN], Gdis[MaxN];/*f(x) = g(x) + h(x)*/
int Queue[MaxN*MaxN];
void prepare(int st, int ed, int n) { /*SPFA*/
	int a, b, c;
	int Queue[n*n], Qt = 0, Used[n+1], tn;
	for(a = 1; a <= n; a++)	Hdis[a] = MaxV, Used[a] = 0;
	Queue[0] = ed, Used[ed] = 1, Hdis[ed] = 0;
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a], Used[tn] = 0;
		for(b = RevNL[tn], c = 0; c < RevNT[tn]; b++, c++) {
			if(Hdis[tn] + RevD[b].w < Hdis[RevD[b].y]) {
				Hdis[RevD[b].y] = Hdis[tn] + RevD[b].w;
				if(Used[RevD[b].y] == 0) {
					Used[RevD[b].y] = 1, Queue[++Qt] = RevD[b].y;
				}
			}
		}
	}
}
void solve_kpath(int st, int ed, int k, int n) {
	L = 0;
	int OutT[n+1], a, b, tn, tw;
	for(a = 1; a <= n; a++)	OutT[a] = 0, Gdis[n] = MaxV;
	for(a = NodeL[st], b = 0; b < NodeT[st]; a++, b++) {
		L++, insHeap(L, Data[a].y, Data[a].w + Hdis[Data[a].y]);
	}
	while(L) {
		tn = Heap[1].node, tw = Heap[1].v;
		delHeap();
		if(OutT[tn] >= k) continue;
		Gdis[tn] = tw, OutT[tn]++, tw = tw - Hdis[tn];
		if(OutT[tn] == k && tn == ed)	{printf("%d\n", tw);return;}
		for(a = NodeL[tn], b = 0; b < NodeT[tn]; a++, b++) {
			L++, insHeap(L, Data[a].y, tw + Data[a].w + Hdis[Data[a].y]);
		}
	}
	puts("0");
}
main() {
/*	freopen("in1.txt", "rt", stdin);   
	freopen("out1.txt", "w+t", stdout);*/
	int n, m, q, a;
	int x, y, d, p, k, st, ed;
	while(scanf("%d %d %d", &n, &m, &q) == 3) {
		int rt, t;		
		for(a = 1; a <= n; a++)/*init*/
            NodeT[a] = RevNT[a] = 0, NodeL[a] = RevNL[a] = MaxV;
		for(a = 0, t = 0, rt = 0; a < m; a++) {
			scanf("%d %d %d", &x, &y, &d);
			Data[t].x = x, Data[t].y = y, Data[t].w = d, t++;
			NodeT[x]++;
			RevD[rt].x = y, RevD[rt].y = x, RevD[rt].w = d, rt++;
			RevNT[y]++;
		}
		MergeSort(0, t-1, Data);
		MergeSort(0, rt-1, RevD);
        for(a = 0; a < t; a++) {
			NodeL[Data[a].x] = NodeL[Data[a].x] < a ? NodeL[Data[a].x]: a;
			RevNL[RevD[a].x] = RevNL[RevD[a].x] < a ? RevNL[RevD[a].x]: a;
		}
		while(q--) {
			scanf("%d %d %d", &st, &ed, &k);
			prepare(st, ed, n);
			solve_kpath(st, ed, k, n);
		}
	}
	return 0;
}
void Swap(int P, int S) {
    int T;
    T=Heap[P].v, Heap[P].v=Heap[S].v, Heap[S].v=T;
    T=Heap[P].node, Heap[P].node=Heap[S].node, Heap[S].node=T;
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
void insHeap(int site, int node, int t) {/*insert new node*/
    Heap[site].node = node, Heap[site].v = t;
    siftup(site);
}
void delHeap() {/*delete last node*/
    Swap(1, L), L--;
    siftdown(1);
}
void MergeSort(int l, int h, Link Data[]) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l, m, Data);
        MergeSort(m+1, h, Data);
        Merge(l, m, h, Data);
    }
}
void Merge(int l, int m, int h, Link Data[]) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h) {
        if(Data[In1].x < Data[In2].x || (Data[In1].x == Data[In2].x && Data[In1].w <= Data[In2].w))
            X[Top++] = Data[In1++];
        else
            X[Top++] = Data[In2++];
    }
    while(In1 <= m) X[Top++] = Data[In1++];
    while(In2 <= h)    X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
} 
/*
5 10 4
1 2 10
2 1 10
2 3 5
3 2 5
2 5 2
5 2 2
3 4 1
4 3 1
1 3 4
3 1 4
1 2 2
1 3 10
1 4 11
1 5 5
2 2 1
1 2 1
2 1 10
1 2 10
1 1 1
1 1 2
1 1 3
*/
