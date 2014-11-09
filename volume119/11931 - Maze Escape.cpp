#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

int sx, sy, ex, ey, bx, by, cx, cy;
int n, m;
char g[32][32];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int dist[25][25][25][25];
int bfs() {
	memset(dist, 0, sizeof(dist));
	dist[sx][sy][bx][by] = 1;
	queue<int> X, Y, BX, BY;
	int x, y, tx, ty, ttx, tty;
	X.push(sx), Y.push(sy), BX.push(bx), BY.push(by);
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		bx = BX.front(), BX.pop();
		by = BY.front(), BY.pop();
		int step = dist[x][y][bx][by];
		for (int i = 0; i < 4; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if (g[tx][ty] == 'd' && g[bx][by] == 'b')
				return step;
			if (g[tx][ty] == '#' || g[tx][ty] == 'd')
				continue;
			if (tx == bx && ty == by) { // push it
				ttx = tx + dx[i], tty = ty + dy[i];
				if (ttx < 0 || tty < 0 || ttx >= n || tty >= m)
					continue;
				if (g[ttx][tty] == '#' || g[ttx][tty] == 'd')
					continue;
				if (dist[tx][ty][ttx][tty] == 0) {
					dist[tx][ty][ttx][tty] = step + 1;
					X.push(tx), Y.push(ty), BX.push(ttx), BY.push(tty);
				}
			} else {
				if (dist[tx][ty][bx][by] == 0) {
					dist[tx][ty][bx][by] = step + 1;
					X.push(tx), Y.push(ty), BX.push(bx), BY.push(by);
				}
			}
		}
	}
	return -1;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == '@')
					sx = i, sy = j;
				if (g[i][j] == 'd')
					ex = i, ey = j;
				if (g[i][j] == 'x')
					bx = i, by = j;
				if (g[i][j] == 'b')
					cx = i, cy = j;
			}
		}
		int ret = bfs();
		if (ret < 0)	
			puts("No Way!");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
3 3

d.b
.@.
x.#

3 5
...d.
.#x#.
...@b

0 0
*/
