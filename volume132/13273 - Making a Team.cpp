#include <bits/stdc++.h>
using namespace std;

int64_t mpow(int64_t x, int64_t y, int64_t m) {
	if (y < 0)	return 0;
	int64_t ret = 1;
	while (y) {
		if (y&1)
			ret = (ret*x)%m;
		y >>= 1, x = (x*x)%m;
	}
	return ret;
}
int main() {
	int64_t n;
	const int64_t MOD = 100000007;
	while (scanf("%lld", &n) == 1 && n) {
		int64_t ret = 0;
		/*
			\sum_{i=1}^{n} \binom{n}{i} i^4
				= 2^{n-1} n + 2^{n-2} n(n-1) \times 7
					+ 2^{n-3} n(n-1)(n-2) \times 6
					+ 2^{n-4} n(n-1)(n-2)(n-3)
		*/
		ret += (n*mpow(2, n-1, MOD))%MOD;
		ret += (7*n*(n-1)%MOD*mpow(2, n-2, MOD))%MOD;
		ret += (6*n*(n-1)%MOD*(n-2)%MOD*mpow(2, n-3, MOD))%MOD; 
		ret += (n*(n-1)%MOD*(n-2)%MOD*(n-3)%MOD*mpow(2, n-4, MOD))%MOD; 
		ret %= MOD;
		printf("%lld\n", ret);
	}
	return 0;
}
