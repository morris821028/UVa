#include <stdio.h> 

const long long mod = 1000000009LL;
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
} 
int main() {
	int testcase, n;
	long long div2 = mpow(2, mod-2, mod);
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long p = 1, x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			p *= (1 + x * 2);
			p %= mod;
		}
		p = ((p - 1) * div2)%mod;
		printf("%lld\n", p);
	}
	return 0;
}
