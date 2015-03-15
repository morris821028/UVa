#include <stdio.h>
long long mul(long long a, long long b, long long mod) {
	long long ret = 0;
//	for( ; b != 0; b>>=1, (a<<=1)%=mod)
//		if(b&1) (ret += a) %= mod;
	// above common format, but easy get TLE. below limit mod = 10^x
	long long a1, a2, b1, b2;
    a1 = a/1000000, a2 = a%1000000;
    b1 = b/1000000, b2 = b%1000000;
    ret = a2*b1*1000000%mod + b2*a1*1000000%mod + a2*b2;
    ret %= mod;
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

// K1^K2 = K2 mod 10^12
// sieve condition, K1^K2 = K2 mod 10^1, K1^K2 = K2 mod 10^2, ...
long long K1, K2, t10[20];
int dfs(int idx, long long k2) {
	if (idx == 12) {
		if (mpow(K1, k2, t10[idx]) == k2%t10[idx]) {
			K2 = k2;
			return 1;
		}
		return 0;
	}
	for (int i = (idx == 11); i <= 9; i++) {
		long long x = t10[idx] * i + k2;
		if (mpow(K1, x, t10[idx]) == x%t10[idx]) {
			if (dfs(idx+1, x))
				return 1; 
		}
	}
	return 0;
}
int main() {
	t10[0] = 1;
	for (int i = 1; i < 20; i++)
		t10[i] = t10[i-1] * 10;
	int cases = 0;
	while (scanf("%lld", &K1) == 1 && K1) {
		dfs(0, 0);
		printf("Case %d: ", ++cases);
		printf("Public Key = %lld Private Key = %lld\n", K1, K2);
	}
	return 0;
}
