#include <stdio.h>
#define MAXV (100*1005)

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, x[105], sum = 0;
		scanf("%d", &n);
		char dp[MAXV] = {};
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x[i]);
			sum += x[i];
		}
		for (int i = 0; i < n; i++) {
			int v = x[i];
			for (int j = sum; j >= v; j--)
				dp[j] |= dp[j-v];
		}
		int ret = 0;
		for (int i = sum/2; i >= 0; i--) {
			if (dp[i])
				ret = i, i = -1;
		}
		printf("%d\n", sum - ret);
	}
	return 0;
}
