#include <bits/stdc++.h>
using namespace std;
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = x * x %mod;
	}
	return ret;
}
int main() {
	long long n, m, k, x;
	while (scanf("%lld %lld %lld %lld", &n, &m, &k, &x) == 4) {
		long long ret = (mpow(10, k, n)*m%n + x)%n;
		printf("%lld\n", ret);
	}
	return 0;
}

