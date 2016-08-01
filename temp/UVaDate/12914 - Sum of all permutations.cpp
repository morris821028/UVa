// Euler's theorem, math
// similar problem Ad Infinitum 8 - Math Programming Contest Value of all Permutations
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
const long long MOD = 1711276033;
const int MAXN = 1000005;
long long f[MAXN], S[MAXN], A[MAXN];
long long C(int n, int m, long long MOD) {
	return f[n] * inverse(f[m], MOD) % MOD * inverse(f[n-m], MOD) % MOD;
}
/*
	thanks for dreamoon !
*/
int main() {
	f[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		f[i] = f[i-1] * i;
		if (f[i] >= MOD)	f[i] %= MOD;
	}
	int N; 
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			A[i] = i+1;
			
		S[0] = 0;
		for (int i = 1; i <= N; i++)
			S[i] = (S[i-1] + A[i-1])%MOD;
		
		for (int i = 1; i <= N; i++) {
			long long ret;
			ret = S[i];
			ret = ret * f[N - i] % MOD;
			ret = ret * f[i - 1] % MOD;
			ret = ret * C(N, i-1, MOD) % MOD;
			printf("%lld%c", ret, i == N ? '\n' : ' ');
		}
	}
	return 0;
}
/*
*/
