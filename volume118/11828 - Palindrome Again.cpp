// TLE
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
using namespace std;

int main() {
	int testcase, cases = 0, N, K;
	char s[1024];
	long long dp[2][1024];
	long long mod = 1000000000LL;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %s", &N, &K, s);
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		int froll = 0, L = N/2 + N%2;
		for(int i = 0; i < N; i++)
			s[i] = tolower(s[i]);
		for(int i = 0; i < L; i++) {
			memset(dp[!froll], 0, sizeof(dp[!froll]));
			int diff, cos;
			diff = s[i] == s[N - i - 1] ? 0 : 1;
			cos = i == N - i - 1 ? 1 : 2;
			for(int j = 0; j <= K; j++) {
				if(diff) {
					dp[!froll][j + 2] += dp[froll][j] * 24;
					dp[!froll][j + 1] += dp[froll][j] * 2;
				} else {
					dp[!froll][j + cos] += dp[froll][j] * 25; // using diff
					dp[!froll][j] += dp[froll][j];
				}
				dp[!froll][j] %= mod;
			}
			froll = !froll;
		}
		long long ret = 0;
		for(int i = 0; i <= K; i++)
			ret = (ret + dp[froll][i])%mod;
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
