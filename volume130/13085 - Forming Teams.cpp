#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1e9+7;
const int32_t MAXN = 1000005;
int64_t invf[MAXN], f[MAXN];

void sieve() {
	f[0] = f[1] = 1;
	invf[0] = 1, invf[1] = 1;
	const int64_t p = MOD;
	for (int i = 2; i < MAXN; i++) {
		int t = p/i, k = p%i;
		int64_t fk = invf[k];
		int64_t fk2 = fk*fk;
		if (fk2 >= MOD)	fk2 %= MOD;
		invf[i] = i*t%MOD*t%MOD*fk2%MOD;
	}
	for (int i = 2; i < MAXN; i++)
		invf[i] = (invf[i-1]*invf[i])%MOD;
	for (int i = 2; i < MAXN; i++)
		f[i] = (f[i-1]*i)%MOD;
}
int64_t mpow(int64_t x, int64_t y, int64_t mod) {
	int64_t ret = 1;
	while (y) {
		if (y&1)
			ret = (ret*x)%mod;
		y >>= 1, x = (x*x)%mod;
	}
	return ret;
}
void exgcd(int64_t x, int64_t y, int64_t &g, int64_t &a, int64_t &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
int64_t inverse(int64_t x, int64_t p) {
    int64_t g, b, r;
    exgcd(x, p, g, r, b);
    if (g < 0)	r = -r;
    return (r%p + p)%p;
}
int64_t solve(int N, int x) {
	int64_t t, y = N/x;
	t = (f[N] * invf[x])%MOD;
	t = (t * inverse(mpow(f[y], x, MOD), MOD))%MOD;
	return t;
}

int main() {
	sieve();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N;
		scanf("%d", &N);
		int64_t ret = 0;
		for (int i = 1; i*i <= N; i++) {
			if (N%i)
				continue;
			ret += solve(N, i);
			if (ret >= MOD)	ret -= MOD;
			if (i*i != N) {
				ret += solve(N, N/i);
				if (ret >= MOD)	ret -= MOD;
			}
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
3
1
3
10
*/

