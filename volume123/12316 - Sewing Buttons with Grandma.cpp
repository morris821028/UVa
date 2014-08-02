#include <stdio.h> 

long long C[128][128], A[128];
int main() {
	for(int i = 1; i < 128; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	int n, m;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		for(int i = 1; i <= m; i++)
			scanf("%lld", &A[i]);
		long long dp[128][128] = {};
		
		dp[0][0] = 1;
		for(int i = 1; i <= m; i++) {
			for(int j = 0; j <= n; j++) {
				for(int k = 0; k <= A[i] && j + k <= n; k++)
					dp[i][j + k] += dp[i - 1][j] * C[j + 1 + k][k];
			}
		}
		printf("%lld\n", dp[m][n]);
	}
	return 0;
}
/*
1 3
3
1
1
3 2
4
2
3 2
1
1
*/
