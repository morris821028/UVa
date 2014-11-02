#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int g[32][32], gdir[32][32][4];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
void bfs(int sx, int sy, int ex, int ey) {
	queue<int> X, Y;
	int used[32][32] = {}, from[32][32][2] = {};
	int tx, ty, x, y;
	X.push(sx), Y.push(sy);
	used[sx][sy] = 1;
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		for (int i = 0; i < 4; i++) {
			if (!gdir[x][y][i])	continue;
			tx = x + dx[i], ty = y + dy[i];
			if (abs(g[tx][ty] - g[x][y]) > 10)
				continue;
			if (!used[tx][ty]) {
				used[tx][ty] = used[x][y] + 1;
				from[tx][ty][0] = x, from[tx][ty][1] = y;
				X.push(tx), Y.push(ty);
			}
		}
	}
	if (!used[ex][ey]) {
		printf("There is no acceptable route from %d-%d to %d-%d.\n", sx, sy, ex, ey);
		return ;
	}
	int path[512][2], n = 0, ttx, tty;
	tx = ex, ty = ey;
	do {
		path[n][0] = tx, path[n][1] = ty, n++;
		if (tx == sx && ty == sy)	break;
		ttx = from[tx][ty][0], tty = from[tx][ty][1];
		tx = ttx, ty = tty;
	} while (true);
	printf("%d-%d", sx, sy);
	for (int i = n - 2; i >= 0; i--)
		printf(" to %d-%d", path[i][0], path[i][1]);
	puts("");
}
int main() {
	int sx, sy, ex, ey;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &g[i][j]);
		memset(gdir, 0, sizeof(gdir));
		while (scanf("%d %d %d %d", &sx, &sy, &ex, &ey) == 4 && sx) {
			if (sx == ex && sy < ey) {
				for (int i = sy; i < ey; i++)
					gdir[sx][i][0] = 1;
			} else if (sx == ex && sy > ey) {
				for (int i = sy; i > ey; i--)
					gdir[sx][i][1] = 1;
			} else if (sy == ey && sx < ex) {
				for (int i = sx; i < ex; i++)
					gdir[i][sy][2] = 1;
			} else if (sy == ey && sx > ex) {
				for (int i = sx; i > ex; i--)
					gdir[i][sy][3] = 1;
			}
		}
		while (scanf("%d %d %d %d", &sx, &sy, &ex, &ey) == 4 && sx) {
			if (cases++)	puts("");
			if (sx == ex && sy == ey)
				printf("To get from %d-%d to %d-%d, stay put!\n", sx, sy, ex, ey);
			else {
				bfs(sx, sy, ex, ey);
			}
		}
	}
	return 0;
}
/*
3 4
10 15 20 25
19 30 35 30
10 19 26 20
1 1 1 4
2 1 2 4
3 4 3 3
3 3 1 3
1 4 3 4
2 4 2 1
1 1 2 1
0 0 0 0
1 1 2 2
2 3 2 3
2 2 1 1
0 0 0 0 
*/
