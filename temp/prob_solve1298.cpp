#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	long long n;
	int m, d, cases = 0;
	while (scanf("%lld %d", &n, &m) == 2) {
		char buf[32];
		sprintf(buf, "%lld", n);
		d = strlen(buf);
		long long low = -(1LL<<59), upp = 1LL<<59;
		for (int i = (1<<10) - 1; i > 0; i--) {
			if (__builtin_popcount(i) <= m) {
				int t = 0, pos;
				long long A[10];
				long long dp[32][3] = {}, pre = 0; // < = >
				
				for (int j = 0; j < 10; j++)
					if ((i>>j)&1)	A[t++] = j;
				for (int j = 0; j < d; j++)
					dp[j][0] = dp[j][1] = -(1LL<<59), dp[j][2] = 1LL<<59;
				for (int j = 0; j < d; j++) {
					pre = pre * 10 + buf[j] - '0';
					if (j == 0) {
						dp[0][0] = 0;
						for (int k = 0; k < t; k++) {
							if (A[k] < pre)			dp[j][0] = max(dp[j][0], A[k]);
							else if (A[k] == pre)	dp[j][1] = max(dp[j][1], A[k]);
							else if (A[k] > pre)	dp[j][2] = min(dp[j][2], A[k]);
						}
					} else {
						for (int k = 0; k < t; k++) {
							dp[j][0] = max(dp[j][0], dp[j-1][0] * 10 + A[k]);
							dp[j][2] = min(dp[j][2], dp[j-1][2] * 10 + A[k]);
							if (dp[j-1][1] * 10 + A[k] < pre)
								dp[j][0] = max(dp[j][0], dp[j-1][1] * 10 + A[k]);
							else if (dp[j-1][1] * 10 + A[k] == pre)
								dp[j][1] = max(dp[j][1], dp[j-1][1] * 10 + A[k]);
							else if (dp[j-1][1] * 10 + A[k] > pre)
								dp[j][2] = min(dp[j][2], dp[j-1][1] * 10 + A[k]);
						}
					}
//					printf("%lld %lld %lld\n", dp[j][0], dp[j][1], dp[j][2]);
					low = max(low, max(dp[j][0], dp[j][1]));
					if (dp[j][2] > n)	upp = min(upp, dp[j][2]);
				}
			}
		}
		printf("Case %d: ", ++cases);
		if (llabs(low - n) == llabs(upp - n) && low != upp)
			printf("%lld %lld\n", low, upp);
		else
			printf("%lld\n", llabs(low - n) < llabs(upp - n) ? low : upp);
	}
	return 0;
}
/*
3355798521 10
262004 2
8000 1
1000 1
2243 2
88449 2
123456789 1
7099 2
*/
