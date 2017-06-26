#include <bits/stdc++.h>
using namespace std;

int main() {
	const int MAXN = 32;
	uint64_t dp[MAXN+1][MAXN+1] = {};
	for (int i = 1; i < MAXN; i++)
		dp[i][1] = 1, dp[1][i] = 1;
	for (int i = 2; i < MAXN; i++) {
		for (int j = 2; j < MAXN; j++) {
			dp[i][j] = 0;
			for (int k = 1; k <= i; k++)
				dp[i][j] += dp[k][j-1];
		}
	}
	int testcase, R, C;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &R, &C);
		printf("%lld\n", dp[R][C]);
	}
	return 0;
}
/*
4
2 1
2 2
2 3
3 3
*/
