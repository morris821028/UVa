#include<stdio.h>
main() {
	int n, m, p, a, b;
	long long DP[91][91][16] = {};
	DP[1][0][0] = 1, DP[1][1][1] = 1;
	for(m = 2; m <= 90; m++)
		for(n = 0; n <= m; n++)
			for(p = 0; p <= 15 && p <= n; p++) {
				if(n == 0 && p == 0)
					DP[m][0][0] = 1;
				else if(p == 0) {
					for(a = 0; a <= n && a <= 15; a++)
						DP[m][n][0] += DP[m-1][n][a];
				}
				else if(n == p) {
					for(a = 0; a <= n; a++)
						DP[m][n][n] += DP[m-1][a][n-1];
				}
				else if(p == 1)
					DP[m][n][1] = DP[m-1][n][0];
				else
					DP[m][n][p] = DP[m-1][n][p-1];
		}
	while(scanf("%d %d", &n, &m) == 2) {
		long long Ans = 0;
		for(a = 0; a <= n; a++)
			for(b = 0; b <= n; b++)
				Ans += DP[m][a][b];
		printf("%lld\n", Ans);
	}
	return 0;
}
