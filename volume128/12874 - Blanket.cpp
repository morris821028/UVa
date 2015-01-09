#include <stdio.h> 
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
int ret[131072];
int main() {
	int testcase, n, m;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n);
		ReadInt(&m);
		int A[20][20] = {}, a, b;
		for (int i = 0; i < n; i++) {
//			scanf("%d %d", &a, &b);
			ReadInt(&a);
			ReadInt(&b);
			A[b][a]++;
		}
		for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= 16; j++)
				A[i][j] += A[i][j-1];
		}
		for (int i = 0; i <= n; i++)
			ret[i] = 0;
		for (int i = 0; i < m; i++) {
			int cover = 0;
			for (int j = 1, t; j <= 16; j++) {
				t = i%j;
				cover += A[j][16] - A[j][t];
			}
			ret[cover]++;
		}
		for (int i = 0; i <= n; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}
/*
9999
3 30
2 5
3 5
3 6

2 15
1 2
3 4
*/
