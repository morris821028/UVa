#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1024;
int A[MAXN], B[MAXN], C[MAXN];
vector< pair<int, int> > g[MAXN];
int main() {
	int testcase, n, L, x, y, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &L);
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]), g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(make_pair(y, w));
			g[y].push_back(make_pair(x, w));
		}
		int st = 1, prev = -1;
		for (int i = 1; i <= n; i++)
			if (g[i].size() == 1)
				st = i;
		B[1] = st, C[n] = 0;
		for (int i = 2; i <= n; i++) {
			for (int j = 0; j < g[st].size(); j++) {
				if (g[st][j].first != prev) {
					B[i] = g[st][j].first, C[i-1] = g[st][j].second;
					prev = st, st = g[st][j].first;
					break;
				}
			}
		}
		int dp[MAXN][2];
		memset(dp, 0, sizeof(dp));
		dp[1][0] = dp[1][1] = 0;
		for (int i = 1; i <= n; i++) {
			int sum = 0;
			for (int j = i; j <= n; j++) {
				sum += A[B[j]];
				if (sum >= L) {
					int r = dp[i][0] + 1, c = dp[i][1] + C[j];
					if (r > dp[j+1][0] || (r == dp[j+1][0] && c < dp[j+1][1]))
						dp[j+1][0] = r, dp[j+1][1] = c;
				}
			}
		}
		if (dp[n+1][0] == 0)
			puts("-1");
		else
			printf("%d %d\n", dp[n+1][0], dp[n+1][1]);
	}
	return 0;
}

