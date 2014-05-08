#include <stdio.h>
#include <algorithm>
int main() {
	scanf("%*d");
	for(int n, x, oo = 0x3f3f3f; scanf("%d", &n) == 1;) {
		int dp[10005] = {};
		for(int i = 0; i <= 10000; i++)
			dp[i] = oo;
		dp[0] = 0;
		for(int i = 0, x; i < n; i++) {
			scanf("%d", &x);
			for(int j = x; j <= 10000; j++)
				dp[j] = std::min(dp[j], dp[j - x] + 1);
		}
		scanf("%d", &n);
		printf("%d\n", dp[n] == oo ? 0 : dp[n]);
	}
	return 0;
}
