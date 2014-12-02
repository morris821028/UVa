#include <stdio.h> 
long long mul(long long a, long long b, long long mod) { 
	long long ret = 0; 
	for( ; b != 0; b>>=1, (a<<=1)%=mod) 
		if(b&1) (ret += a) %= mod; 
	return ret; 
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = mul(ret, x, mod);
		y >>= 1, x = mul(x, x, mod);
	}
	return ret;
}
long long solve(long long n, long long b, long long d, long long m) {
	// d * (b^n - 1) / (b - 1) mod m
	long long ret;
	ret = mpow(b, n, (b - 1) * m); // b^n mod (b-1) * m
	ret = (ret + (b - 1) * m - 1)/ (b - 1);
	ret = mul(ret, d, m);
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n, b, d, m, ret;
		scanf("%lld %lld %lld %lld", &n, &b, &d, &m);
		ret = solve(n, b, d, m);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

