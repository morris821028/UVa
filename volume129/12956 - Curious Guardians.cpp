#include <bits/stdc++.h>
// http://codeforces.com/blog/entry/20335#comment-251217
const int MAXN = 128;
const long long mod = 1e9 + 7;
long long C[MAXN][MAXN] = {}, dp[MAXN][MAXN];
int N, K;
long long dfs(int n, int k) {
	// node label between [1, n+1], and label 1 as root which limied degree k
	if (n <= 1)
		return 1;	
	if (k == 0)
		return 0;
	if (k == 1)
		return (n * dfs(n-1, K-1))%mod;
	if (dp[n][k] != -1)
		return dp[n][k];
	long long &ret = dp[n][k];
	ret = 0;
	// root 1 has at most $k$ subtrees
	// pick one subtree has $i$ node (ways = C(n, i), and choose root of subtree way = i)
	// dp(n, k) = \sum C(n, i) * i * dp(i-1, K-1) * dp(n-i, k-1)
	// in order to eliminate overcounting, make picked subtree has smallest label.
	// modify C(n, i) to C(n-1, i-1)
	for (int i = 1; i <= n; i++) {
		long long sum = (C[n-1][i-1] * i)% mod;
		sum *= dfs(i-1, K-1);
		sum %= mod;
		sum *= dfs(n-i, k-1);
		sum %= mod;
		ret += sum;
		ret %= mod;
	}
	return ret;
}
int main() {
	C[0][0] = 1;
	for (int i = 0; i < MAXN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
	}
	
	while (scanf("%d %d", &N, &K) == 2) {
		memset(dp, -1, sizeof(dp));
		long long ret = dfs(N-1, K);
		printf("%lld\n", ret);
	}
	return 0;
}
