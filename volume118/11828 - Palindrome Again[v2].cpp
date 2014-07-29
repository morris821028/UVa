#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
using namespace std;

long long dp1[1024][1024], dp2[1024][1024];
long long mod = 1000000000LL;
/*
P= number of characters where a[i] = a[n-i-1];
Q= number of characters where a[i] != a[n-i-1];
*/
long long solve(int P, int Q, int K) {
	long long ret = 0;
	for(int i = 0; i <= K; i++)
		ret = (ret + dp1[P][i] * dp2[Q][K - i])%mod;
	return ret;
}
int main() {
	dp1[0][0] = dp2[0][0] = 1;
	// dp1(P, K), dp2(Q, K)
	for(int i = 1; i < 1024; i++) {
		for(int j = 0; j < 1024; j++) {
			if(j >= 2)
				dp1[i][j] += dp1[i - 1][j - 2] * 25;
			dp1[i][j] += dp1[i - 1][j];
			if(j >= 1)
				dp2[i][j] += dp2[i - 1][j - 1] * 2;
			if(j >= 2)
				dp2[i][j] += dp2[i - 1][j - 2] * 24;
			dp1[i][j] %= mod, dp2[i][j] %= mod;
		}
	}
	// 
	for(int i = 0; i < 1024; i++) {
		for(int j = 1; j < 1024; j++)
			dp2[i][j] = (dp2[i][j] + dp2[i][j-1])%mod;
	}
	
	int testcase, cases = 0, N, K;
	char s[1024];
	
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %s", &N, &K, s);
		int P = 0, Q = 0;
		for(int i = 0; i < N/2; i++) {
			P += s[i] == s[N - i - 1];
			Q += s[i] != s[N - i - 1];
		}
		long long ret = 0;
		if(N&1)
			ret = (solve(P, Q, K) + solve(P, Q, K - 1) * 25) %mod;
		else
			ret = solve(P, Q, K);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
