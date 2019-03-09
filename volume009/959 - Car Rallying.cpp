#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXS = 25;
int tick[MAXN];
int limit[MAXN][MAXS];
int dp[MAXN][MAXS];
int main() {
	int testcase;
	int A, B, N, V;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &A, &B);
		A /= 10, B /= 10;
		int n = 0;
		while (scanf("%d %d", &N, &V) == 2) {
			if (N == 0 && V == 0)
				break;
			V /= 10;
			for (int i = 0; i < N; i++)
				tick[n++] = V;
		}

		tick[n++] = 10000;
		for (int i = 0; i < n; i++) {
			limit[i][0] = tick[i];
			for (int j = 1; j < MAXS && i+j < n; j++)
				limit[i][j] = min(limit[i][j-1], tick[i+j]);
		}
		
		for (int i = 0; i <= n; i++)
			memset(dp[i], 0x3f, sizeof(dp[i]));
		const int INF = dp[0][0];
		dp[0][0] = 0;
		for (int i = 0; i < n; i++) {
			for (int v = 0; v < MAXS; v++) {
				if (dp[i][v] == INF)
					continue;
				int w = dp[i][v];
				for (int a = (v == 0); a <= A; a++) {
					int u = min(i + v + a - 1, n-1);
					if (limit[i][u-i] >= v+a) {
						dp[u+1][v+a] = min(dp[u+1][v+a], 1+w);
					} else {
						break;
					}
				}
				for (int b = 0; b <= B && b < v; b++) {
					int u = min(i + v - b - 1, n-1);
					if (limit[i][u-i] >= v-b) {
						dp[u+1][v-b] = min(dp[u+1][v-b], 1+w);
					}
				}
			}
		}
		
		int ret = INF;
		for (int i = 0; i < MAXS; i++)	
			ret = min(ret, dp[n][i]);
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
30 10
10 100 5 70 3 40 6 100 0 0
40 50
15 100 0 0
40 20
1 50 1 40 1 30 1 20 1 10 1 20 1 30 1 40 1 50 0 0
*/
