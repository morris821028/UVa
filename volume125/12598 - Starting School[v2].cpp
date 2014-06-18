#include <stdio.h>
#include <algorithm>
using namespace std;
int A[65536], B[65536], C[65536], D[65536];
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
	int testcase, cases = 0, N, K, Q;
	int x, l, r;
	ReadInt(&testcase);
	while(testcase--) {
		ReadInt(&N);
		ReadInt(&K);
		ReadInt(&Q);
		int *p = A + 1, *q = B + 1;
		for(int i = 1; i <= K; i++, p++, q++) {
			ReadInt(p), *q = *p;
		}
		sort(B + 1, B + 1 + K);
		B[0] = 0, B[K+1] = N + 1;
		int M = 1;
		C[0] = 0;
		p = B, q = p+1;
		for(int i = 1; i <= K + 1; i++, p = q++) {
			l = *p + 1, r = *q - 1;
			if(l <= r) {
				C[M] = C[M - 1] + r - l + 1;
				D[M] = l;
				M++;
			}
		}
		printf("Case %d:\n", ++cases);
		int prevX = 0, prevP = 0, pos;
		while(Q--) {
			ReadInt(&x);
			if(x <= K)
				printf("%d\n", A[x]);
			else {
				x -= K;
				if(x >= prevX)
					pos = lower_bound(C + prevP, C + M, x) - C;
				else
					pos = lower_bound(C, C + prevP, x) - C;
				printf("%d\n", D[pos] + x - C[pos-1] - 1);
				prevX = x, prevP = pos;
			}
		}
	}
	return 0;
}
/*
2
10 4 4
1 3 5 2
5 6 9 10
10 3 2
10 1 9
4 10
*/
