#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;

int N, M, K;
int g[32][32], sum[32][32];
int dp[32][32][32][32], used[32][32][32][32], testcase = 0;
int getArea(int x, int y, int w, int h) {
	return sum[x + w-1][y + h-1] - sum[x-1][y + h-1] - sum[x + w-1][y-1] + sum[x-1][y-1];
}
int dfs(int x, int y, int w, int h) {
	if (used[x][y][w][h] == testcase)
		return dp[x][y][w][h];
	if (getArea(x, y, w, h) < 2)
		return 0;
	used[x][y][w][h] = testcase;
	int &ret = dp[x][y][w][h];
	ret = 0x3f3f3f3f;
	for (int i = 1; i < w; i++) {
		if (getArea(x, y, i, h) > 0 && getArea(x+i, y, w-i, h) > 0)
			ret = min(ret, dfs(x, y, i, h) + dfs(x+i, y, w-i, h) + h);
	}
	for (int i = 1; i < h; i++) {
		if (getArea(x, y, w, i) > 0 && getArea(x, y+i, w, h-i) > 0)
			ret = min(ret, dfs(x, y, w, i) + dfs(x, y+i, w, h-i) + w);
	}
	return ret;
}
int main() {
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		memset(g, 0, sizeof(g));
		memset(sum, 0, sizeof(sum));
		int x, y;
		for (int i = 0; i < K; i++) {
			scanf("%d %d", &x, &y);
			g[x][y]++;
		}
		for (int i = 1; i <= N; i++) {
			int x = 0;
			for (int j = 1; j <= M; j++) {
				x += g[i][j];
				sum[i][j] = sum[i-1][j] + x;
			}
		}
		testcase++;
		printf("Case %d: %d\n", testcase, dfs(1, 1, N, M));
	}
	return 0;
}
