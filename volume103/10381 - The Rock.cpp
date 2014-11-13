#include <stdio.h>
#include <string.h>
#include <queue>
#include <assert.h>
#include <algorithm>
using namespace std;

char g[64][64];
int dist[64][64], walldist[64][64][4];
int n, m;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
struct State {
	int x, y;
	int g, h;
	State(int a=0, int b=0, int c=0, int d=0):
		x(a), y(b), g(c), h(d) {}
	bool operator<(const State &a) const {
		return h > a.h;
	}
};
int dp[40][40][40 * 40];
int search(int sx, int sy, int ex, int ey) {
	priority_queue<State> pQ;
	State u, v;
	int tx, ty, h;
	pQ.push(State(sx, sy, 0, 0));
	memset(dp, 63, sizeof(dp));
	while (!pQ.empty()) {
		u = pQ.top(), pQ.pop();
		if (u.h > dp[u.x][u.y][u.g])
			continue;
		if (u.x == ex && u.y == ey)
			return u.h;
		for (int i = 0; i < 4; i++) {
			tx = u.x + dx[i], ty = u.y + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if (g[tx][ty] == '#' || g[tx][ty] == 'E')
				continue;
			if (g[tx][ty] == '.') 
				h = max(u.h, u.g + walldist[u.x][u.y][i]);
			else if (g[tx][ty] == 'X')
				h = max(u.h, u.g);
			assert(u.g + 1 < 40 * 40);
			if (dp[tx][ty][u.g + 1] > h) {
				dp[tx][ty][u.g + 1] = h;
				pQ.push(State(tx, ty, u.g + 1, h));
			}
		}
	}
	return 0;
}
void bfs(int sx, int sy) {
	memset(dist, 63, sizeof(dist));
	queue<int> X, Y;
	int tx, ty;
	X.push(sx), Y.push(sy);
	dist[sx][sy] = 0;
	while (!X.empty()) {
		sx = X.front(), X.pop();
		sy = Y.front(), Y.pop();
		for (int i = 0; i < 4; i++) {
			tx = sx + dx[i], ty = sy + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if (g[tx][ty] == '#' || dist[tx][ty] <= dist[sx][sy] + 1)
				continue;
			dist[tx][ty] = dist[sx][sy] + 1;
			X.push(tx), Y.push(ty);
		}
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		int sx, sy, ex, ey, tx, ty;
		
		memset(walldist, 0, sizeof(walldist));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == 'E')	sx = i, sy = j;
				if (g[i][j] == 'X')	ex = i, ey = j;				
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] != '.')
					continue;
				g[i][j] = '#';
				bfs(ex, ey);
				for (int k = 0; k < 4; k++) {
					tx = i + dx[k], ty = j + dy[k];
					if (tx < 0 || ty < 0 || tx >= n || ty >= m)
						continue;
					if (g[tx][ty] == '#')
						continue;
					walldist[tx][ty][(k+2)%4] = dist[tx][ty];
				}
				g[i][j] = '.';
			}
		}
		int ret = search(sx, sy, ex, ey);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2

8 8
..X.....
........
##.##...
........
##.##...
##.##...
........
..E.....
 
3 4
..X.
.##.
.E..
*/
