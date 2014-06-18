#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int x, y, v;
}Edge;
int cmp(const void *i, const void *j) {
	Edge *a, *b;
	a = (Edge *)i, b = (Edge *)j;
	return a->v - b->v;
}
int P[10001], R[10001];
void MakeSet(int n) {
	static int i;
	for(i = 0; i <= n; i++)
		P[i] = i, R[i] = 1;
}
int FindP(int x) {
	if(P[x] != x)
		P[x] = FindP(P[x]);
	return P[x];
}
void Link(int x, int y) {
	if(R[x] < R[y])
		P[x] = y, R[y] += R[x];
	else
		P[y] = x, R[x] += R[y];
}
int Union(int x, int y, int *val) {
	x = FindP(x), y = FindP(y);
	if(x != y) {
		Link(x, y);
		(*val) = (*val) - 1;
		return 1;
	}
	return 0;
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int t, N, M, A, i, C = 0, tM;
	Edge D[100000];
	ReadInt(&t);
	while(t--) {
		ReadInt(&N), ReadInt(&M), ReadInt(&A);
		for(i = 0, tM = 0; i < M; i++) {
			ReadInt(&D[tM].x), ReadInt(&D[tM].y), ReadInt(&D[tM].v);
			if(D[tM].v < A)	tM++;
		}
		qsort(D, tM, sizeof(Edge), cmp);
		/*Disjoint Sets*/
		MakeSet(N);
		int val = N, cost = 0;
		for(i = 0; i < tM; i++)
			cost += D[i].v*Union(D[i].x, D[i].y, &val);
		printf("Case #%d: %d %d\n", ++C,cost+val*A, val);
	}
    return 0;
}
