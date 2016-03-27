#include <bits/stdc++.h>
using namespace std;
const long long mod = 9999959999;
long long dp[2048][2048];
int used[2048][2048] = {};
long long dfs(int u, int v) {
	if (u == 0 && v == 0)	return 1;
	if (used[u][v])	return dp[u][v];
	used[u][v] = 1;
	long long &ret = dp[u][v];
	ret = 1;
	if (u > 0)
		ret = ret + dfs(u-1, v+1);
	if (v > 0)
		ret = ret + dfs(u, v-1);
	ret %= mod;
	return ret;
}
int main() {
	int A, B;
	while (scanf("%d %d", &A, &B) == 2) {
		if (A == 0 && B == 0)
			break;
		printf("%lld\n", dfs(A, B));
	}
	return 0;
}

