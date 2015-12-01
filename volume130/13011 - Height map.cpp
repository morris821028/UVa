#include <bits/stdc++.h>
using namespace std;

int used[128][128][5];
int g[128][128] = {}, n, m;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int valid(int x, int y) {
	return x >= 1 && y >= 1 && x <= n && y <= m;
}
int hasface(int x, int y, int k) {
	if (k == 0)	return 1;
	if (k == 1)
		return !valid(x-1, y) || g[x][y] > g[x-1][y];
	if (k == 2)
		return !valid(x+1, y) || g[x][y] > g[x+1][y];
	if (k == 3)
		return !valid(x, y-1) || g[x][y] > g[x][y-1];
	if (k == 4)
		return !valid(x, y+1) || g[x][y] > g[x][y+1];
}
int hasconnect(int ax, int ay, int bx, int by, int f) {
	int lx, ly, rx, ry;
	if (f == 1) {
		lx = g[ax-1][ay], rx = g[ax][ay];
		ly = g[bx-1][by], ry = g[bx][by];
	} else if (f == 2) {
		lx = g[ax+1][ay], rx = g[ax][ay];
		ly = g[bx+1][by], ry = g[bx][by];
	} else if (f == 3) {
		lx = g[ax][ay-1], rx = g[ax][ay];
		ly = g[bx][by-1], ry = g[bx][by];
	} else if (f == 4) {
		lx = g[ax][ay+1], rx = g[ax][ay];
		ly = g[bx][by+1], ry = g[bx][by];
	}
	return max(lx, ly) < min(rx, ry);
}
void dfs(int x, int y, int f) {
	if (!valid(x, y) || used[x][y][f])
		return ;
	used[x][y][f] = 1;
	if (f == 0) {
		for (int i = 0; i < 4; i++) {
			int tx = x + dx[i], ty = y + dy[i];
			if (!valid(tx, ty))
				continue;
			if (g[x][y] == g[tx][ty])
				dfs(tx, ty, f);
		}
	} else {
		if (f == 1 || f == 2) {
			for (int i = 0; i < 2; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if (!valid(tx, ty))
					continue;
				if (hasface(tx, ty, f) && hasconnect(x, y, tx, ty, f))
					dfs(tx, ty, f);
			}
		} else {
			for (int i = 2; i < 4; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if (!valid(tx, ty))
					continue;
				if (hasface(tx, ty, f) && hasconnect(x, y, tx, ty, f))
					dfs(tx, ty, f);
			}
		}
	}
}
int countFace(int n, int m) {
	int faces = 0;
	for (int k = 0; k < 5; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (used[i][j][k])
					continue;
				if (hasface(i, j, k)) {
					dfs(i, j, k);
					faces++;
				}
			}
		}
	}
	return faces + 1;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		memset(g, 0, sizeof(g));
		memset(used, 0, sizeof(used));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &g[i][j]);
		printf("%d\n", countFace(n, m));
	}
	return 0;
}

