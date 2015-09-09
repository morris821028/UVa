#include <bits/stdc++.h>
using namespace std;

int A[16][16], S[16][16] = {};
int dp[16][16][16][16][16];
int used[16][16][16][16][16];
int area(int lx, int rx, int ly, int ry) {
	return S[rx][ry] - S[rx][ly-1] - S[lx-1][ry] + S[lx-1][ly-1];
}
int dfs(int lx, int rx, int ly, int ry, int k) {
	if (used[lx][rx][ly][ry][k])
		return dp[lx][rx][ly][ry][k];
	int &ret = dp[lx][rx][ly][ry][k];
	used[lx][rx][ly][ry][k] = 1;
	ret = 0x3f3f3f3f;
	if (k == 1)	return ret = (area(lx, rx, ly, ry) * area(lx, rx, ly, ry));
	int val;
	for (int i = lx; i < rx; i++) {
		val = area(lx, i, ly, ry);
		ret = min(ret, val * val + dfs(i+1, rx, ly, ry, k-1));
		val = area(i+1, rx, ly, ry);
		ret = min(ret, val * val + dfs(lx, i, ly, ry, k-1));
	}
	for (int i = ly; i < ry; i++) {
		val = area(lx, rx, ly, i);
		ret = min(ret, val * val + dfs(lx, rx, i+1, ry, k-1));
		val = area(lx, rx, i+1, ry);
		ret = min(ret, val * val + dfs(lx, rx, ly, i, k-1));
	}
	return ret;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				scanf("%d", &A[i][j]);
		for (int i = 1; i <= 8; i++) {
			int s = 0;
			for (int j = 1; j <= 8; j++) {
				s += A[i][j];
				S[i][j] = S[i-1][j] + s;
			}
		}
		memset(used, 0, sizeof(used));
		int v = dfs(1, 8, 1, 8, n);
		double a = (double)v / n;
		double b = (double) S[8][8] / n;
		printf("%.3lf\n", sqrt(a - b*b));
	}
	return 0;
}

