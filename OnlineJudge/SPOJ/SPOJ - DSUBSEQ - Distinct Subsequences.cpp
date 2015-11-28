#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;
const int MOD = 1000000007;
char s[131072];
int dp[MAXN], sum[MAXN], table[256];
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s+1);
		int n = strlen(s+1);
		memset(table, 0, sizeof(table));
		
		// dp[i]   : subsequence end with s[i]
		// sum[i]  : \sum{0 ... i} dp[i]
		// table[i]: last position of s[i]
		dp[0] = 1, sum[0] = 1;
		for (int i = 1; i <= n; i++) {
			dp[i] = sum[i-1];
			if (table[s[i]])
				dp[i] -= sum[table[s[i]] - 1];
			if (dp[i] < MOD)	dp[i] += MOD;
			if (dp[i] >= MOD)	dp[i] %= MOD;
			sum[i] = sum[i-1] + dp[i];
			if (sum[i] >= MOD)	sum[i] %= MOD;
			table[s[i]] = i;
		}
		printf("%d\n", sum[n]);
	}
	return 0;
}

