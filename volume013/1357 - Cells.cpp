#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 300005;
const int MAXM = 20000005;
int L[MAXN], R[MAXN];
int A[MAXM], B[MAXM];
int n;

void build(int u) {
	static int stk[MAXN];
	int stkIdx = -1, stamp = 0;
	stk[++stkIdx] = u;
	A[u] = 0;
	while (stkIdx >= 0) {
		u = stk[stkIdx];
		if (A[u]) {
			stkIdx--;
			B[u] = ++stamp;
			continue;
		}
		A[u] = ++stamp;
		for (int i = L[u], j = L[u]+R[u]; i < j; i++) {
			if (i < n) {
				A[i] = 0;
				stk[++stkIdx] = i;
			} else {
				A[i] = ++stamp;
				B[i] = ++stamp;
			}
		}
	}
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
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main() {
	int testcase, cases = 0;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		ReadInt(&n);
		for (int i = 0; i < n; i++)
//			scanf("%d", &R[i]);
			ReadInt(&R[i]);
		L[0] = 1;
		for (int i = 1; i < n; i++)
			L[i] = L[i-1]+R[i-1];
		build(0);
		
		int q, x, y;
//		scanf("%d", &q);
		ReadInt(&q);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			if (A[x] < A[y] && B[y] < B[x])
				puts("Yes");
			else
				puts("No");
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2
6
3 2 1 1 0 2
5
0 1
2 4
3 5
1 8
6 9

5
2 0 3 0 1
4
2 6
1 6
2 3
3 5
*/
