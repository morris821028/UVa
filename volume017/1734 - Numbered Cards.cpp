#include <bits/stdc++.h>
using namespace std;

void brute_check(int stat[], int n) {
	int cc[1024] = {};
	for (int i = 1; i <= n; i++) {
		int t = i, mark = 0;
		while (t)
			mark |= 1<<(t%10), t /= 10;
		cc[mark]++;
	}
	for (int i = 1; i < 1024; i++) {
		if (cc[i] != stat[i]) {
			printf("%d %d %d\n", i, cc[i], stat[i]);
		}
	}
}

const long long MOD = 1000000007;
int main() {
	int cases = 0, testcase;
	char s[32];
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int len = strlen(s);
		sscanf(s, "%d", &n);
		
		int stat[1024] = {};
		{
			int dp[2][1024][2] = {};	// [iterator][digit bit-set][less]
			
			dp[0][0][0] = 1;
			int p = 0, q = 1;
			for (int it = 0; it < len; it++) {
				memset(dp[q], 0, sizeof(dp[q]));
				int c = s[it]-'0';
				for (int i = 0; i < 1024; i++) {
					if (dp[p][i][1]) {
						if (i) {
							for (int j = 0; j < 10; j++)
								dp[q][i|(1<<j)][1] += dp[p][i][1];
						} else {
							dp[q][i][1] += dp[p][i][1];
							for (int j = 1; j < 10; j++)
								dp[q][i|(1<<j)][1] += dp[p][i][1];
						}
					}
					if (dp[p][i][0]) {
						dp[q][i|(1<<c)][0] += dp[p][i][0];
						if (i) {
							for (int j = 0; j < c; j++)
								dp[q][i|(1<<j)][1] += dp[p][i][0];
						} else {
							if (c)
								dp[q][i][1] += dp[p][i][0];
							for (int j = 1; j < c; j++)
								dp[q][i|(1<<j)][1] += dp[p][i][0];
						}
					}
				}
				p = 1-p, q = 1-q;
			}

			for (int i = 2; i < 1024; i++)
				stat[i] = dp[p][i][0] + dp[p][i][1];
	//		brute_check(stat, n);
		}
		
		{
			int64_t dp[2][1024] = {};
			dp[0][0] = 1;
			int p = 0, q = 1;
			for (int i = 0; i < 1024; i++) {
				if (stat[i] == 0)
					continue;
				for (int j = 0; j < 1024; j++)
					dp[q][j] = dp[p][j];
				int v = stat[i];
				for (int j = 0; j < 1024; j++) {
					if (i&j)
						continue;
					dp[q][i|j] += (dp[p][j] * stat[i])%MOD;
					if (dp[q][i|j] >= MOD)
						dp[q][i|j] -= MOD;
				}
				
				p = 1-p, q = 1-q;
			}
			
			int64_t ret = 0;
			for (int i = 0; i < 1024; i++) {
				ret += dp[p][i];
				if (ret >= MOD)
					ret -= MOD;
			}
			printf("Case %d: %lld\n", ++cases, (ret + MOD-1)%MOD);
		}
	}
	return 0;
}

