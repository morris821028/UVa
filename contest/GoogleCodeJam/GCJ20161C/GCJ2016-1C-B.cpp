#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	int B;
	long long M;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %lld", &B, &M);
		long long dp[64] = {};
		int g[64][64] = {};
		dp[0] = 1;
		for (int i = 0; i < B; i++) {
			for (int j = i+1; j < B; j++)
				g[i][j] = 1, dp[j] += dp[i];
		}
		
		for (int i = B-2; i >= 0; i--) {
			if (dp[B-1] - dp[i] >= M) {
				dp[B-1] -= dp[i];
				g[i][B-1] = 0;
			}
		}
		printf("Case #%d: %s\n", ++cases, M == dp[B-1] ? "POSSIBLE" : "IMPOSSIBLE");
		if (M == dp[B-1])
		for (int i = 0; i < B; i++) {
			for (int j = 0; j < B; j++)
				printf("%d", g[i][j]);
			puts("");
		}
	}
	return 0;
}

