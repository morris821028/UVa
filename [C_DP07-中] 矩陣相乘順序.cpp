#include <stdio.h>
int x[105], dp[105][105], arg[105][105];
void dfs(int l, int r) {
	if(l + 1 == r) {
		printf("M%d", l + 1);
		return;
	}
	putchar('('), dfs(l, arg[l][r]), dfs(arg[l][r], r), putchar(')');
}
int main() {
	for(int n; scanf("%d", &n) == 1;) {
		for(int i = 0; i < n; i++)
			scanf("%d %d", &x[i], &x[i + 1]);
		n++;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++)
				dp[i][j] = 0x3f3f3f3f;
			dp[i][i + 1] = 0;
		}
		for(int i = 1; i < n; i++) {
			for(int j = 0; i + j < n; j++) {
				for(int k = j + 1; k <= i + j; k++) {
					if(dp[j][i + j] > dp[j][k] + dp[k][i + j] + x[j] * x[k] * x[i + j])
						dp[j][i + j] = dp[j][k] + dp[k][i + j] + x[j] * x[k] * x[i + j], arg[j][i + j] = k;
				}
			}
		}
		dfs(0, n - 1);
		printf("\n%d\n", dp[0][n - 1]);
	}
	return 0;
}
