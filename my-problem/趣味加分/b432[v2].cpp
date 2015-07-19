#include <bits/stdc++.h> 
using namespace std;

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
		vector<long long> A(1, 0);
		for (int i = 0; i < 20; i++) {
			vector<long long> nA;
			for (auto &a : A) {
				long long t, mask;
				t = mpow(a, E, M), mask = (1LL<<(i+1))-1;
				if ((t&mask) == (n&mask)) {
					nA.push_back(a);
				} 
				t = mpow(a|(1LL<<i), E, M), mask = (1LL<<(i+1))-1;
				if ((t&mask) == (n&mask)) {
					nA.push_back(a|(1LL<<i));
				}			
			}
			A = nA;
		}
		assert(A.size() == 1 && mpow(A[0], E, M) == n);
		printf("%lld\n", A[0]);
	}
	return 0;
}
