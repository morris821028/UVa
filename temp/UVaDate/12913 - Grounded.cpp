// Euler's theorem, math
// similar problem Ad Infinitum 10 - Math Programming Contest Number of zero-xor subsets 
#include <stdio.h> 
#include <algorithm>
using namespace std;

void exgcd(long long x, long long y, long long &g, long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long mul(long long a, long long b, long long mod) { 
	long long ret = 0; 
	for ( ; b != 0; b>>=1, (a<<=1)%=mod) 
		if (b&1) (ret += a) %= mod; 
	return ret; 
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	} 
	return ret;
}
long long inverse(long long x, long long MOD) {
	return mpow(x, MOD-2, MOD);
}
const long long MOD = 1000000007;
const int MAXN = 1000005;
long long f[MAXN];
long long C(int n, int m, long long MOD) {
	return f[n] * inverse(f[m], MOD) % MOD * inverse(f[n-m], MOD) % MOD;
}

void brute(int N, int K) {
	N = 1<<N;
	int ret = 0;
	for (int i = 0; i < (1<<N); i++) {
		int x = 0;
		for (int j = 0; j < N; j++)
			if ((i>>j)&1)
				x = x ^ j;
		if (__builtin_popcount(x) == K)
			ret++;
	}
	printf("%d\n", ret);
}
/*
	simple problem, let XOR(V) = 0
	let N = 2, we have S = {0, 1, 2, 3}
	
	for any subset V, assume XOR(V) = x
		if x in V, V' = V - {x}
		otherwise, V' = V + {x}.
	sat. XOR(V') = 0
	
	example. 
		V = {2, 3} => V' = {1, 2, 3}
		
	so there are 2^N element, number of subset is 2^(2^N).
	but V' has duplicate, add {x} & remove {y} will make same V'.
	add/remove {x}, x is unique number which can be anything in S.
	so V' will occur 2^N times.
	
	finally, result = 2^(2^N) / 2^N
*/
/*
	thanks for dreamoon !
*/
int main() {
	f[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		f[i] = f[i-1] * i;
		if (f[i] >= MOD)	f[i] %= MOD;
	}
	long long N, K;
	while (scanf("%lld %lld", &N, &K) == 2) {
		if (K > N) {
			printf("0\n");
			continue;
		}
		// 2^(2^N) / 2^N
		long long ret;
		// Euler's theorem
		ret = mpow(2, mpow(2, N, MOD-1), MOD);
		ret = ret * inverse(mpow(2, N, MOD), MOD) % MOD;
		ret = ret * C(N, K, MOD) % MOD;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3 1
4 1
4 2
4 3
4 4
1000000 1
*/
