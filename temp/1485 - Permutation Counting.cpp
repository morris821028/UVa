#include <stdio.h> 

const long long MOD = 1000000007;
const int MAXN = 1024;
long long dp[MAXN][MAXN] = {};
/*
	{1, (3), 2, 4}
	=> add 5
	(0) none
		{1, (3), 2, 4, 5}
	(1) swap with E-position
		{1, (5), 2, 4, 3}
	(2) swap other position
		{1, (3), 2, (5), 4}
		{1, (3), (5), 4, 2}
		{(5), (3), 2, 4, 1}
*/
int main() {
	dp[1][0] = 1;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 0; j <= i; j++) {
			dp[i+1][j] = (dp[i+1][j] + dp[i][j] * (j + 1))%MOD;
			dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j] * (i - j))%MOD;
		}
	}
	int N, K;
	while (scanf("%d %d", &N, &K) == 2)
		printf("%lld\n", dp[N][K]);
	return 0;
}
