#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN 128
char s[MAXN];
long long dp[MAXN][MAXN][11];
long long C[MAXN][MAXN] = {};
const long long mod = 1000000007LL;
int main() {
	C[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j])%mod;
	}

	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		int digit[11] = {}, sum[11] = {};
		for (int i = 0; i < n; i++)
			digit[s[i] - '0']++;
		digit[10] = digit[0];
		for (int i = 1; i <= 10; i++)
			sum[i] = sum[i-1] + digit[i];
		memset(dp, 0, sizeof(dp));
		int m = 0;
		int half = n/2 + n%2;
		dp[0][0][0] = 1;
		for (int i = 1; i <= 10; i++) {
			for (int j = 0; j <= digit[i]; j++) {
				for (int k = 0; k <= half; k++) {
					for (int l = 0; l < 11; l++) {
						long long way = dp[i-1][k][l];
						if (way == 0)	continue;
						int p = sum[i-1] - k;
						if (p < 0)	continue;
						int l1 = j, l2 = digit[i] - j;
//						printf("%d %d %d %d %d\n", i, k, l, k + l1, p + l2);
						if (k + l1 > n - half)	continue;
						if (p + l2 > half)		continue;
						if (n%2 == 0 && i == 10) { // append 0
							way = way * C[k + l1 - 1][l1]%mod;
						} else {
							way = way * C[k + l1][l1]%mod;
						}
						if (n%2 != 0 && i == 10) { // append 0
							way = way * C[p + l2 - 1][l2]%mod;
						} else {
							way = way * C[p + l2][l2]%mod;
						}
						int t = ((l + l1 * (i == 10 ? 0 : i) - l2 * (i == 10 ? 0 : i))%11 + 11)%11;
						dp[i][k+l1][t] += way;
						dp[i][k+l1][t] %= mod;
//						printf("%d %d %d %lld\n", i, k+l1, t, dp[i][k+l1][t]);
					}
				}
			}
		}
		printf("%lld\n", dp[10][n - half][0]);
	}
	return 0;
}
/*
2090
16510
201400000000000000000000000000
*/
