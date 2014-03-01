#include<stdio.h>
typedef struct Point {
    int x, y, tag;
}Point;
Point P[10000], X[10000], FP[10000];
void MergeSort(int, int);
void Merge(int, int, int);
int cross1(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int cross2(Point a, Point b, Point c, Point d) {/*ab x cd*/
	int x1, x2, y1, y2;
	x1 = a.x - b.x, y1 = a.y - b.y;
	x2 = c.x - d.x, y2 = c.y - d.y;
	return x1 * y2 - x2 * y1;
}
int farthest_pair(int N) {
    MergeSort(0, N-1);
    int a, b, l = 0, u = 0;
    Point L[N], U[N];
    for(a = 0; a < N; a++) {
        while(l >= 2 && cross1(L[l-2], L[l-1], P[a]) <= 0)
            l--;
        while(u >= 2 && cross1(U[u-2], U[u-1], P[a]) >= 0)
            u--;
        L[l++] = P[a];
        U[u++] = P[a];
    }
    if(u-2 >= 0)	L[l] = U[u-2];
    int Max = 0, t = 0;
    for(a = 0, b = u-1; a < l && b > 0; ) {
		if(Max <= (L[a].x-U[b].x)*(L[a].x-U[b].x) + (L[a].y-U[b].y)*(L[a].y-U[b].y)) {
			if(Max != (L[a].x-U[b].x)*(L[a].x-U[b].x) + (L[a].y-U[b].y)*(L[a].y-U[b].y))
				t = 0;
			Max = (L[a].x-U[b].x)*(L[a].x-U[b].x) + (L[a].y-U[b].y)*(L[a].y-U[b].y);
			FP[t] = L[a], FP[t+1] = U[b], t+=2;
		}
		if(cross2(L[a+1], L[a], U[b-1], U[b]) < 0)
			a++;
		else
			b--;
	}
	for(a = 0; a < t; a++)
		printf("%d %d     /////////////////\n", FP[a].x, FP[a].y);
	return t;
}
main() {
    int N, M, a, b;
    while(scanf("%d", &N) == 1) {
        for(a = 0; a < N; a++)
            scanf("%d,%d", &P[a].x, &P[a].y), P[a].tag = a;
        M = farthest_pair(N);
        int Max, t;
        for(a = 0; a < N; a++) {
			Max = 0;
			for(b = 0; b < M; b++) {
				t = (P[a].x - FP[b].x)*(P[a].x - FP[b].x) +
				(P[a].y - FP[b].y)*(P[a].y - FP[b].y);
				Max = (Max > t) ? Max : t;
			}
			P[a].y = Max, P[a].x = P[a].tag;
		}
		MergeSort(0, N-1);
		for(a = 0; a < N; a++) {
			printf("%d\n", P[a].y);
		}
    }
    return 0;
}/*
6
1,1
2,1
4,1
6,1
-1,-1
1,1
2,1
4,1
6,1
2,1
6,1
-1,-1
1,1
2,1
3,1
4,1
*/
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
