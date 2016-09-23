#include <stdio.h>
#include <limits.h>

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int x[1024], sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x[i]);
			sum += x[i];
		}
		int *dp = calloc(sum/2+1, sizeof(int));
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			int u = x[i];
			for (int j = sum/2; j >= u; j--)
				dp[j] |= dp[j-u];
		}
		long long ret = -1;
		for (int i = sum/2; i >= 0; i--) {
			if (dp[i]) {
				ret = (long long)i*i + (long long)(sum-i)*(sum-i);
				break;
			}
		}
		free(dp);
		printf("%lld\n", ret);
	}
	return 0;
}
