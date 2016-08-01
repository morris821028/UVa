#include <stdio.h> 
#include <string.h>
#include <algorithm> 
using namespace std;

long long dp[70][70][70][2] = {}; // [n][select][#operator][status] = ways
int main() {
	dp[0][0][0][0] = 1;
	for (int i = 0; i <= 64; i++) {
		for (int j = 0; j <= 64; j++) {
			for (int k = 0; k <= 64; k++) {
				dp[i+1][j+1][k][1] += dp[i][j][k][1];
				dp[i+1][j][k+1][0] += dp[i][j][k][1];
				
				dp[i+1][j][k][0] += dp[i][j][k][0];
				dp[i+1][j+1][k+1][1] += dp[i][j][k][0];
			}
		}
	}
	int n, m, cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		if (n == 0 && m == 0)
			break;
		long long a = 0, b = 0;
		for (int j = m; j <= n; j++) {
			for (int i = 0; i <= n; i++) {
				if (i < j)
					a += dp[n][j][i][0] + dp[n][j][i][1];
				if (i > j)
					b += dp[n][j][i][0] + dp[n][j][i][1];
			}
		}
		printf("Case %d: %lld %lld\n", ++cases, a, b);
	}
	return 0;
}
/*
5 3
10 3
0 0
*/
