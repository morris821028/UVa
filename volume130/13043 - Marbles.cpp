#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MOD = 1000000007;
const int MAXK = 55;
int64_t f[MAXN], inv_f[MAXN];
inline int64_t pmod(int64_t a, int64_t b, int32_t m) {
	a = a * b;
	if (a >= m)
		return a%m;
	return a;
}
void init() {
	const int n = 100005; 
	static int64_t inv[MAXN];
	inv[1] = 1;
	for (int i = 2; i < n; i++)
		inv[i] = MOD - pmod(MOD/i, inv[MOD%i], MOD);
	f[0] = 1, inv_f[0] = 1;
	for (int i = 1; i < n; i++)
		f[i] = pmod(f[i-1], i, MOD);
	for (int i = 1; i < n; i++)
		inv_f[i] = pmod(inv_f[i-1], inv[i], MOD);
}
int64_t C(int n, int m) {
	return pmod(pmod(f[n], inv_f[m], MOD), inv_f[n-m], MOD);
}

int64_t dp[MAXN][MAXK];
int main() {
	init();
	int testcase, cases = 0;
	int N, K, X;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &K, &X);
		dp[0][0] = 1;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= K; j++) {
				int64_t ret = 0;
				if (i >= X)
					ret += pmod(pmod(j, dp[i-X][j-1], MOD), C(i-1, X-1), MOD);
				ret += pmod(j, dp[i-1][j], MOD);
				if (ret >= MOD)
					ret %= MOD;
				dp[i][j] = ret;
			}
		}
		printf("Case %d: %lld\n", ++cases, dp[N][K]);
	}
	return 0;
}
/*
3
4  2  2
10  5  3
900  5  20
*/
