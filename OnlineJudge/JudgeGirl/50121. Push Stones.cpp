#include <stdio.h>
#include <string.h>

int main() {
	int n, m, o;
	int x, y, w;
	static int g[505][505] = {};
	int cmd;
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &x, &y, &w);
	scanf("%d", &o);
	for (int i = 0; i < o; i++) {
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w), g[x][y] = w;
	}

	while (scanf("%d", &cmd) == 1) {
		if (cmd == 0) {
			g[x][y] = w;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++)
					printf("%d%c", g[i][j], " \n"[j == m-1]);
			}
			g[x][y] = 0;
			continue;
		}
		cmd--;
		static const int dx[] = {0, 1, 0, -1};
		static const int dy[] = {1, 0, -1, 0};
		int tx, ty, e = 0, c = 0;
		tx = x+dx[cmd], ty = y+dy[cmd];
		while (tx >= 0 && tx < n && ty >= 0 && ty < m && g[tx][ty] && e <= w)
			e += g[tx][ty], c++, tx += dx[cmd], ty += dy[cmd];
		if (e <= w && tx >= 0 && tx < n && ty >= 0 && ty < m) {
			w -= e;
			x += dx[cmd], y += dy[cmd];
			if (cmd&1) {
				while (c--) {
					g[tx][ty] = g[tx-dx[cmd]][ty-dy[cmd]];
					tx -= dx[cmd], ty -= dy[cmd];
				}
			} else {
				if (cmd == 0)
					memmove(&g[x][y+1], &g[x][y], c*sizeof(g[0][0]));
				else
					memmove(&g[tx][ty], &g[tx][ty+1], c*sizeof(g[0][0]));
				tx = x, ty = y;
			}
			g[tx][ty] = 0;
		}
	}
	return 0;
}
