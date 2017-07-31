#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
int main() {
	int n;
	static int a[MAXN], d[MAXN];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &a[i], &d[i]);
			
		static int dp[2][MAXN][2]; // [2][location][2]
		const int INF = 0x3f3f3f3f;
		memset(dp, 0, sizeof(dp));
		int p = 0, q = 1;
		for (int i = n-2; i >= 0; i--) {
			for (int j = i+1; j < n; j++) {	// complete [i, j], p = i+1, q = i
				dp[q][j][0] = min(dp[p][j][0]+a[i+1]-a[i], dp[p][j][1]+a[j]-a[i]);
				if (dp[q][j][0] >= d[i])
					dp[q][j][0] = INF;
				dp[q][j][1] = min(dp[q][j-1][0]+a[j]-a[i], dp[q][j-1][1]+a[j]-a[j-1]);
				if (dp[q][j][1] >= d[j])
					dp[q][j][1] = INF;
			}
			p = 1-p, q = 1-q;
		}
		int ret = min(dp[p][n-1][0], dp[p][n-1][1]);
		if (ret == INF)
			puts("No solution");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
5
1 3
3 1
5 8
8 19
10 15
*/
