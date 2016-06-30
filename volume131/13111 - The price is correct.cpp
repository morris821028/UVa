#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;
int G[1024][MAXN][MAXN];
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, M, P, SX, SY;
		scanf("%d %d %d", &N, &M, &P);
		scanf("%d %d", &SX, &SY);
		
		memset(G, 0, sizeof(G));
		int T = 0;
		for (int i = 0; i < P; i++) {
			int x, y, t, v;
			scanf("%d %d %d %d", &x, &y, &t, &v);
			G[t][x][y] = v;
			T = max(T, t);
		}
		
		int dp[MAXN][MAXN];
		const int dx [] = {0, 0, 1, -1, 0};
		const int dy [] = {1, -1, 0, 0, 0};
		memset(dp, -1, sizeof(dp));
		dp[SX][SY] = 0;
		for (int t = 1; t <= T; t++) {
			int next[MAXN][MAXN];
			memcpy(next, dp, sizeof(dp));
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (dp[i][j] == -1)
						continue;
					for (int k = 0; k < 5; k++) {
						int tx = i + dx[k];
						int ty = j + dy[k];
						if (tx < 1 || ty < 1 || tx > N || ty > M)
							continue;
						next[tx][ty] = max(next[tx][ty], dp[i][j] + G[t][tx][ty]);
					}
				}
			}
			memcpy(dp, next, sizeof(dp));
//			for (int i = 1; i <= N; i++, puts("")) {
//				for (int j = 1; j <= M; j++)
//					printf("%3d ", next[i][j]);
//			}
//			puts("----");
		}
		
		int ret = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++)
				ret = max(ret, dp[i][j]);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
1
4  3  4
1  1
1  2  1  10
3  1  3  5
3  3  3  15
2  1  4  15

2
2 3 4
1 3
2 1 1 5
1 3 1 7
2 1 5 3
1 1 1 6
*/

