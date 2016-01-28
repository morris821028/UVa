#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4096;
double dp[MAXN][MAXN], dpw[MAXN], dpv[MAXN];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, K;
		double P;
		scanf("%d %d %lf", &N, &K, &P);
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= i; j++) {
				dp[i+1][j] += dp[i][j] * (1-P);
				dp[i+1][j+1] += dp[i][j] * P;
			}
			dpw[i] = 0;
			for (int j = K; j <= i; j++)
				dpw[i] += dp[i][j];
		}
		
		memset(dpv, 0, sizeof(dpv));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= i; j++) {
				dpv[i] = max(dpv[i], dpw[j] + dpv[i-j]);
			}
		}
		
		double ret = dpv[N];
		printf("Case #%d: %.9lf\n", ++cases, ret);
	}
	return 0;
}

