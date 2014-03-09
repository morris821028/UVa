#include <stdio.h>
int dp[1005][1005], s[1005][1005];
int main() {
	int testcase;
	int i, j, k;
	int n;
	int A[1005], SUM[1005];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		for(i = 1, SUM[0] = 0; i <= n; i++)
			SUM[i] = SUM[i-1] + A[i];
		for(i = 1; i <= n; i++)
			dp[i][i] = A[i], s[i][i] = i;
		for(i = 1; i < n; i++) {
			for(j = 1; i+j <= n; j++) {
				int l = j, r = i+j;
				dp[l][r] = 0x7f7f7f7f;
				for(k = s[l][r-1]; k <= s[l+1][r]+1; k++) {
					int tmp = dp[l][k-1] + dp[k+1][r] + SUM[r] - SUM[l-1];
					if(tmp < dp[l][r]) {
						dp[l][r] = tmp;
						s[l][r] = k;
					}
				}
			}
		}
		printf("%d\n", dp[1][n]);
	}
	return 0;
}
