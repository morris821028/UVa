#include <stdio.h>
int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
long long gcd(long long x, long long y) {
	int t;
	while (x%y)	t = x, x = y, y = t%y;
	return y;
}
int main() {
	long long x, ret = 1;
	while (scanf("%lld", &x) == 1)
		ret = ret / gcd(x, ret) * x;
	printf("%lld\n", ret);
	return 0;
}

