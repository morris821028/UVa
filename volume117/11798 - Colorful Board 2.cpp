#include <stdio.h>
const long long mod = 1000000007LL;
long long dp[256][256], C[256][256];
int main() {
	C[0][0] = 1;
	for(int i = 1; i < 256; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) %mod;
	}
	dp[0][0] = 1;
	for(int i = 1; i < 256; i++) {
		for(int j = 1; j <= i; j++)
			dp[i][j] = (dp[i-1][j] + dp[i-1][j-1])*j %mod;
	}
	int testcase, cases = 0;
	int N, M, K;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &N, &M, &K);
		N++, M++;
		int x = N*M/2, y = N*M - x;
		long long ret = 0;
		for(int i = 1; i <= K; i++) {
			for(int j = 1; i+j <= K; j++) {
				ret += (C[K][i] * dp[x][i]%mod) * (C[K-i][j] * dp[y][j]%mod) %mod;
				ret %= mod;
			}
		}
		if(N == 1 && M == 1)	ret = K;
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
