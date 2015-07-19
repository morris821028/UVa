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
unsigned long long mpow(unsigned long long x, unsigned long long y, unsigned long long mod) {
	unsigned long long ret = 1;
	while (y) {
		if (y&1) 
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret % mod;
}

// find a^23333 = n \mod 2^32
int main() {
	const long long M = 1LL<<20;
	const long long E = 23333;
	long long n;
	while (scanf("%lld", &n) == 1) {
		long long a = 0;
		for (int i = 0; i < 32; i++) {
			long long t = mpow(a, E, M), mask = (1LL<<(i+1))-1;
			if ((t&mask) == (n&mask)) {
				
			} else {
				a |= 1LL<<i;
			}			
		}
		printf("%lld\n", a);
	}
	return 0;
}
/*
513
3239987713
*/
