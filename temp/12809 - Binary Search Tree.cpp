#include <stdio.h> 
#include <string.h> 
double f[128];
double sum[128], w[128][128];
double dp[128][128];
int arg[128][128];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%lf", &f[i]);
		sum[0] = 0;
		for (int i = 1; i <= n; i++)
			sum[i] = sum[i-1] + f[i];
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++)
				w[i][j] = sum[j] - sum[i - 1];
		for (int i = 0; i <= n; i++)
			dp[i][i] = 0, arg[i][i] = i;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; i + j <= n; j++) {
				double mn = 1e+30;
				int idx = -1;
				for (int k = arg[j][i+j-1]; k <= arg[j+1][i+j]; k++) {
					double t = dp[j][k-1] + dp[k+1][i+j] + w[j][k-1] + w[k+1][i+j];
					if (t < mn)
						mn = t, idx = k;
				}
				dp[j][i+j] = mn, arg[j][i+j] = idx;
			}
		}
		printf("%lf\n", dp[1][n] + 1);
	}
	return 0;
}
