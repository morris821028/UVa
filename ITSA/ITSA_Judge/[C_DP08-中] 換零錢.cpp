#include <stdio.h>

int main() {
	int dp[15005] = {1}, d[4] = {1, 5, 10, 50}, n;
	for(int i = 0; i < 4; i++)
		for(int j = d[i]; j <= 15000; j++)
			dp[j] += dp[j - d[i]];
	scanf("%d", &n);
	printf("%d\n", dp[n]);
	return 0;
}
