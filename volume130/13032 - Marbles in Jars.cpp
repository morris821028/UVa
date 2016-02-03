#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, M[128];
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &M[i]);
		sort(M+1, M+1+N);
		
		long long dp[128][128] = {};
		dp[0][0] = 1;
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j <= M[i]; j++) {
				if (j - (i-1) >= 0) {
					dp[i][j] = dp[i][j] + dp[i-1][j] * (j - (i-1));
					dp[i][j] %= MOD;
				}
				for (int k = j+1; k <= M[i]; k++) {
					dp[i][k] = dp[i][k] + dp[i-1][j];
					dp[i][k] %= MOD;
				}
			}
		}
		
		long long ret = 0;
		for (int i = 0; i <= M[N]; i++)
			ret = (ret + dp[N][i])%MOD;
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

