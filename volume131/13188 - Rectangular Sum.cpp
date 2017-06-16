#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1e9+7;
void exgcd(int64_t x, int64_t y, int64_t &g, int64_t &a, int64_t &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
int64_t inverse(int64_t x, int64_t p) {
    int64_t g, b, r;
    exgcd(x, p, g, r, b);
    if (g < 0)	r = -r;
    return (r%p + p)%p;
}
const int64_t inv2 = inverse(2, MOD);
const int64_t inv6 = inverse(6, MOD);
int64_t f(int64_t n, int64_t i) {	// 1 <= i <= n
	n %= MOD, i %= MOD;
	int64_t a = (n+1-i)*(i*i%MOD*i%MOD+i)%MOD*inv2%MOD;
	int64_t b = 0;
	b = (b + n*(n+1)%MOD*(2*n+1)%MOD*inv6%MOD)%MOD;
	b = (b + n*(n+1)%MOD*inv2%MOD)%MOD;
	b = (b - i*(i+1)%MOD*(2*i+1)%MOD*inv6%MOD)%MOD;
	b = (b - i*(i+1)%MOD*inv2%MOD)%MOD;
	b = b*i%MOD*inv2%MOD;
	b = (b - i*(n-i)%MOD*i%MOD*(i+1)%MOD*inv2%MOD)%MOD;
	return ((a+b)%MOD+MOD)%MOD;
//	int64_t a = (n+1-i)*(i*i*i+i)/2;
//	int64_t b = 0;
//	b = (n*(n+1)*(2*n+1)/6+n*(n+1)/2);
//	b -= (i*(i+1)*(2*i+1)/6+i*(i+1)/2);
//	b = b*i/2;
//	b -= i*(n-i)*(i)*(i+1)/2;
	return a+b;
}
int main() {
	int testcase;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t n, ret = 0;
		scanf("%lld", &n);
		ret = f(n, n/2+1);
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}
