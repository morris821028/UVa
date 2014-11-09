#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0, n, m, A[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		int dp[55][305];
		pair<int, int> from[55][305];
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0, from[0][0] = make_pair(-1, -1);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++)
				dp[i][j] = dp[i-1][j], from[i][j] = from[i-1][j];
			for (int j = A[i]; j <= m; j++) {
				dp[i][j] = min(dp[i][j], min(dp[i][j-A[i]] + 1, dp[i-1][j-A[i]] + 1));
				if (dp[i][j] == dp[i-1][j-A[i]] + 1)
					from[i][j] = make_pair(i-1, j-A[i]);
				if (dp[i][j] == dp[i][j-A[i]] + 1)
					from[i][j] = make_pair(i, j-A[i]);
			}
		}
		printf("Case %d: ", ++cases);
		if (dp[n][m] == 0x3f3f3f3f)
			puts("impossible");
		else {
			printf("[%d]", dp[n][m]);
			int s = m;
			pair<int, int> p = from[n][m], q;
			while (p.first != -1) {
				printf(" %d", s - p.second);
				s = p.second;
				p = from[p.first][p.second];
			}
			puts("");
		}
	}
	return 0;
}
/*
3
6 100
16 17 23 24 39 40
3 50
10 15 20
2 25
7 13
*/
