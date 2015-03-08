#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 128
#define MAXK 256 
int g[MAXN][MAXN], dp[MAXK][MAXN], A[MAXK];
int main() {
	int testcase, N, M, K, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &M);
		memset(g, 0, sizeof(g));
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			g[x][y] = g[y][x] = 1;
		}
		for (int i = 1; i <= N; i++)
			g[i][i] = 1;
		scanf("%d", &K);
		for (int i = 1; i <= K; i++)
			scanf("%d", &A[i]);
		memset(dp, 63, sizeof(dp));
		dp[0][1] = 0;
		for (int i = 0; i < K; i++) {
			for (int j = 1; j <= N; j++) {
				for (int k = 1; k <= N; k++) {
					if (i == 0 || g[j][k])
						dp[i+1][k] = min(dp[i+1][k], dp[i][j] + (A[i+1] != k));
				}
			}
		}
		int ret = 0x3f3f3f3f;
		for (int i = 1; i <= N; i++)
			ret = min(ret, dp[K][i]);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 
7 9 
1 2 
2 3 
2 4 
2 6 
3 4 
4 5 
5 6 
7 4 
7 5 
9 1 2 2 7 5 5 5 7 4 
7 9 
1 2 
2 3 
2 4 
2 6 
3 4 
4 5 
5 6 
7 4 
7 5 
9 1 2 2 6 5 5 5 7 4
*/
