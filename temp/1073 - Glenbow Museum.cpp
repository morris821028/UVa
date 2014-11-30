#include <stdio.h> 

long long dp[1024][5][2], ret[1024];
// dp[#R][#RR][tail R(0) or O(1)]
int main() {
	for (int k = 0; k < 2; k++) {
		dp[1][0][k] = 1;
		for (int i = 2; i < 1024; i++) {
			for (int j = 0; j < 5; j++) {
				dp[i][j][k] = dp[i-1][j][k];
				if (j)
					dp[i][j][k] += dp[i-1][j-1][k];
			}
		}
	}
	for (int i = 1; i < 1024; i++) {
		int r = (i + 4)/2;
		if (i < 4 || i%2)
			ret[i] = 0;
		else
			ret[i] = dp[r][3][0] + dp[r][4][1] + dp[r][4][0];
	}
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n)
		printf("Case %d: %lld\n", ++cases, ret[n]);
	return 0;
}
