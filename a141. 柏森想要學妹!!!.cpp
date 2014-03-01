#include<stdio.h>
#define MaxV 1000000
void MergeSort(int, int);
void Merge(int, int, int);
struct Link {
    short x, y, w;
}Data[1001], X[1001];
int NodeT[1001], NodeL[1001];
void Print_Path(int now, int L[], int flag) {
	if(L[now] != -1)	Print_Path(L[now], L, 0);
	printf("%d%s", now, flag == 0 ? "->": "\n");
}
int SPFA(int st, int ed, int N) {
    int a, b, c, D[N+1], L[N+1], tn, Queue[100000], Qt = 0;
    char Used[N+1];
	for(a = 0; a <= N; a++)
		D[a] = MaxV, Used[a] = 0;
	Queue[0] = st, D[st] = 0, L[st] = -1;
	if(st == 0) D[ed] = 0, L[ed] = st;
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a], Used[tn] = 0;
		for(b = 0, c = NodeL[tn]; b < NodeT[tn]; b++, c++) {
			if(Data[c].w + D[tn] < D[Data[c].y]) {
				D[Data[c].y] = Data[c].w + D[tn], L[Data[c].y] = tn;
				if(Used[Data[c].y] == 0)
					Used[Data[c].y] = 1, Queue[++Qt] = Data[c].y;
			}
		}
	}
	printf("%d->%d:%d\nPath:", st, ed,D[ed]);
	Print_Path(ed, L, 1);
    return 0;
}
main() {
    int t, n, m, x, y, w, a, C = 0, Q;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(a = 0; a <= n; a++)/*init*/
            NodeT[a] = 0, NodeL[a] = MaxV;
            
        for(a = 0; a < m; a++) {
            scanf("%d %d %d", &x, &y, &w);
            Data[a].x = x, Data[a].y = y, Data[a].w = w;
            Data[a+m].x = y, Data[a+m].y = x, Data[a+m].w = w;
            NodeT[x]++, NodeT[y]++;
        }
        MergeSort(0, 2*m-1);
        for(a = 0; a < 2*m; a++)
            NodeL[Data[a].x] = NodeL[Data[a].x] < a ? NodeL[Data[a].x]: a;
		scanf("%d", &Q);
		while(Q--) {
			scanf("%d %d", &x, &y);
			printf("Case#%d:\n", ++C);
			SPFA(x, y, n);
		}
    }
    puts("GO!! MICHAEL!!Wish you can get your girlfriend!!!");
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
    while(In2 <= h)    X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
}
