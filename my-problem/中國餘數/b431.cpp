#include <bits/stdc++.h> 
using namespace std;

long long mul(long long a, long long b, long long mod) { 
	long long ret = 0; 
	for (a %= mod, b %= mod; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) { 
		if (b&1) {
			ret += a;
			if (ret >= mod)	ret -= mod;
		} 
	} 
	return ret; 
}
void exgcd(long long  x, long long y, long long &g, long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long llgcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
long long inverse(long long x, long long p) {
	long long g, b, r;
	exgcd(x, p, g, r, b);
	if (g < 0)	r = -r;
	return (r%p + p)%p;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1) 
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret % mod;
}
int main() {
	long long C, d, p, q;
	long long N, M, Cp, Cq, Mp, Mq;
	while (scanf("%lld %lld %lld %lld", &C, &d, &p, &q) == 4) {
		N = p * q;
		Mp = mpow(C%p, llgcd(C, p) == 1 ? d%(p-1) : d, p);
		Mq = mpow(C%q, llgcd(C, q) == 1 ? d%(q-1) : d, q);
		Cp = mul(q, inverse(q, p), N);
		Cq = mul(p, inverse(p, q), N);
		M = (mul(Mp, Cp, N) + mul(Mq, Cq, N))%N;
		printf("%lld\n", M);
	}
	return 0;
}
