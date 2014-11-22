#include <stdio.h> 

int main() {
	const int mod = 1000000007;
	int dp[1024] = {};
	dp[1] = 1;
	for (int i = 1; i < 1024; i++) {
		for (int j = 1; i * j < 1024; j++) {
			dp[i*j+1] = (dp[i*j+1] + dp[i])%mod;
		}
	}
	int n, cases = 0;
	while (scanf("%d", &n) == 1) {
		printf("Case %d: %d\n", ++cases, dp[n]);
	}
	return 0;
}
