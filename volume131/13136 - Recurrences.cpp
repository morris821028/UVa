#include <bits/stdc++.h>
using namespace std;

static int tlb[200];
inline static int trans(int &a, int &b, int &c) {
//	int ta = 4*a - 3*b - 3*c;
//	int tb = 5*a - 4*b - 4*c;
//	int tc = b - a;
	int ta = tlb[4*a + 7*b + 7*c];
	int tb = tlb[5*a + 6*b + 6*c];
	int tc = b - a;
	a = ta;
	b = tb;
	if (tc >= 10)
		c = tc - 10;
	else if (tc < 0)
		c = tc + 10;
	else
		c = tc;
//	c = (tc%10 + 10)%10;
}
int f(int a, int b, int c, int64_t n) {
	short dp[10][10][10];
	short sp[10][10][10] = {};
	memset(dp, 0, sizeof(dp));
	int64_t s = 0;
	trans(a, b, c);
	for (int i = 1; i <= n; i++) {
		s = (s+a+b+c)%10;
		if (dp[a][b][c] != 0) {
			int64_t diff = (s-sp[a][b][c])*(((n-i)/(i-dp[a][b][c]))%10);
			int64_t less = (n-i)%(i-dp[a][b][c]);
			s = ((s+diff)%10+10)%10;
			trans(a, b, c);
			for (int j = 0; j < less; j++)
				s = (s+a+b+c)%10, trans(a, b, c);
			return s;
		}
		if (i == n)
			return s;
		dp[a][b][c] = i;
		sp[a][b][c] = s;
		trans(a, b, c);
	}
	return -1;
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
inline int64_t ReadInt64(int64_t *x) {
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
	for (int i = 0; i < 200; i++)
		tlb[i] = i%10;
	int testcase;
	int64_t n;
	int a, b, c;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
		ReadInt64(&n);
		ReadInt(&a), ReadInt(&b), ReadInt(&c);
//		scanf("%llu %d %d %d", &n, &a, &b, &c);
		putchar(f(a, b, c, n)+'0');
		puts("");
	}
	return 0;
}
/*
1
9000000000000000000 1 2 3
*/
