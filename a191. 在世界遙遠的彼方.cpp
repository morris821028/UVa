#include<stdio.h>
typedef struct Point {
    int x, y, tag;
}Point;
Point P[10000], CH[10000*2], X[10000];
void MergeSort(int, int);
void Merge(int, int, int);
int cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int monotone_chain(int N) {
    MergeSort(0, N-1);
    int m = 0, a, t;
    for(a = 0; a < N; a++) {
        while(m >= 2 && cross(CH[m-2], CH[m-1], P[a]) <= 0)
            m--;
        CH[m++] = P[a];
    }
    for(a = N-2, t = m+1; a >= 0; a--) {
        while(m >= t && cross(CH[m-2], CH[m-1], P[a]) <= 0)
            m--;
        CH[m++] = P[a];
    }
    return m--;
}
main() {
    int N, M, a, b;
    int Mmax = 0;
    while(scanf("%d", &N) == 1) {
        for(a = 0; a < N; a++)
            scanf("%d %d", &P[a].x, &P[a].y), P[a].tag = a;
        M = monotone_chain(N);
        int Max, t;
        for(a = 0; a < N; a++) {
			Max = 0;
			for(b = 0; b < M; b++) {
				t = (P[a].x - CH[b].x)*(P[a].x - CH[b].x) +
				(P[a].y - CH[b].y)*(P[a].y - CH[b].y);
				Max = (Max > t) ? Max : t;
			}
			P[a].y = Max, P[a].x = P[a].tag;
		}
		MergeSort(0, N-1);
		for(a = 0; a < N; a++) {
			printf("%d\n", P[a].y);
		}
		Mmax = (Mmax > M) ? Mmax : M;
    }
    printf("%d\n", Mmax);
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
        if(P[In1].x < P[In2].x || (P[In1].x == P[In2].x && P[In1].y < P[In2].y))
            X[Top++] = P[In1++];
        else
            X[Top++] = P[In2++];
    }
    while(In1 <= m) X[Top++] = P[In1++];
    while(In2 <= h)    X[Top++] = P[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        P[b] = X[a];
}
