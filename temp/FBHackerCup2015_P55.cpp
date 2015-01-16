#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

char g[128][128];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const char dv[] = "<^>v";
int dist[4][128][128], n, m;
int valid(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m;
}
char next(char c, int t) {
	static char v[] = "^>v<";
	for (int i = 0; i < 4; i++) {
		if (v[i] == c)
			return v[(i + t)%4];
	}
	assert(false);
}
int test(int t, int x, int y) {
	int tx, ty;
	for (int i = 0; i < 4; i++) {
		tx = x, ty = y;
		while (valid(tx, ty) && g[tx][ty] == '.')
			tx += dx[i], ty += dy[i];
		if (valid(tx, ty) && g[tx][ty] != '#') {
			char c = g[tx][ty];
			if (next(c, t) == dv[i])
				return 1;
//			printf("%c %c %d\n", next(g[tx][ty], t), dv[i], i);
		}
	}
	return 0;
}
void bfs() {
	memset(dist, 0, sizeof(dist));
	int sx, sy, ex, ey;
	int x, y, tx, ty, t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j] == 'S')
				sx = i, sy = j, g[i][j] = '.';
			if (g[i][j] == 'G')
				ex = i, ey = j, g[i][j] = '.';
		}
	}
	dist[0][sx][sy] = 1;
	queue<int> X, Y, T;
	X.push(sx), Y.push(sy), T.push(0);
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		t = T.front(), T.pop();
		int d = dist[t][x][y] + 1;
		if (x == ex && y == ey) {
			printf("%d\n", d - 2);
			return;
		}
		for (int i = 0; i < 4; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if (!valid(tx, ty))
				continue;
			if (g[tx][ty] != '.')
				continue;
			if (test((t+1)%4, tx, ty))
				continue;
			if (dist[(t+1)%4][tx][ty] == 0) {
				dist[(t+1)%4][tx][ty] = d;
				X.push(tx), Y.push(ty), T.push((t+1)%4);
			}
		}
	}
	puts("impossible");
}
int main() {
	freopen("laser_maze.txt", "r", stdin);
	freopen("out.txt", "w+", stdout);
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", &g[i]);
		printf("Case #%d: ", ++cases);
		bfs();
	}
	return 0;
}
/*
999
2 5
##^##
S...G
2 6
###<##
S....G
2 5
##v##
S...G
1 5
S..G<
1 6
S...G<
5 5
S....
.....
.>v..
.^<..
....G
*/
