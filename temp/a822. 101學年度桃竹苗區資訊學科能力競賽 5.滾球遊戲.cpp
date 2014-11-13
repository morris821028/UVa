#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[262144];
int grid[512][512], indeg[262144];
void build(int n, int r, int c) {
	int s = r * n + c, x, y;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = 0;
	for (int t = 0; t < n*n; t++) {
		s = (s + t)%(n*n);
		do {
			x = s/n, y = s%n;
			if (grid[x][y] == 0)	break;
			s = (s + 1)%(n*n);
		} while (true);
		grid[x][y] = t+1;
	} 
}
int dfs(int u) {
	int sz = 1, v;
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i];
		sz += dfs(v);
	}
	return sz;
}
void simulate(int n) {
	for (int i = n * n; i >= 0; i--)
		g[i].clear(), indeg[i] = 0;
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	int tx, ty;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int fall = -1, mn = grid[i][j];
			for (int k = 0; k < 4; k++) {
				tx = i + dx[k], ty = j + dy[k];
				if (tx < 0 || ty < 0 || tx >= n || ty >= n)
					continue;
				if (grid[tx][ty] < mn)
					mn = grid[tx][ty], fall = tx * n + ty;
			}
			if (fall != -1)
				g[fall].push_back(i * n + j), indeg[i * n + j]++;
		}
	}
	int ret = 0, mx = 0;
	for (int i = n*n - 1; i >= 0; i--) {
		if (indeg[i] == 0) {
			ret ++, mx = max(mx, dfs(i));
		}
	}
	printf("%d %d\n", ret, mx);
}
int main() {
	int n, r, c;
	while (scanf("%d %d %d", &n, &r, &c) == 3) {
		build(n, r, c);
		simulate(n);
	}
	return 0;
}
/*
3 1 1
4 0 0
*/
