#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, n, m, A[64];
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		int sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			sum += A[i];
		}
		m = min(m-1, sum);
		int dp[10000][2] = {};
		for (int i = 0; i < n; i++) {
			for (int j = m; j >= A[i]; j--) {
				if (dp[j - A[i]][0] + 1 > dp[j][0]) {
					dp[j][0] = dp[j - A[i]][0] + 1;
					dp[j][1] = dp[j - A[i]][1] + A[i];
				}
				if (dp[j - A[i]][0] + 1 == dp[j][0]) {
					dp[j][1] = max(dp[j][1], dp[j - A[i]][1] + A[i]);
				}
			}
		}
		printf("Case %d: %d %d\n", ++cases, dp[m][0] + 1, dp[m][1] + 678);
	}
	return 0;
}
/*
2
3 100
60 70 80
3 100
30 69 70
*/
