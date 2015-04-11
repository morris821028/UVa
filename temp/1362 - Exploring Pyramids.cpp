#include <stdio.h> 
#include <string.h>
using namespace std;

const int MAXN = 305;
const int mod = 1000000000;
long long dp[MAXN][MAXN];
int main() {
	char s[MAXN];
	while (scanf("%s", s) == 1) {
		memset(dp, 0, sizeof(dp));
		int n = (int) strlen(s);
		for (int i = 0; i < n; i += 2) {
			for (int j = 0; i+j < n; j++) {
				int l = j, r = i+j;
				if (l == r)
					dp[l][r] = 1;
				if (s[l] == s[r])
				for (int k = l + 2; k <= r; k += 2)
					if (s[l] == s[k] && s[k] == s[r])
						dp[l][r] = (dp[l][r] + dp[l+1][k-1] * dp[k][r])%mod;
			}
		}
		printf("%lld\n", dp[0][n-1]);
	}
	return 0;
}
