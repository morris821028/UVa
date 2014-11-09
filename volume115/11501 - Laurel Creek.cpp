#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
int n, m;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
struct state {
	char g[17][17];
	int x, y, log;
	bool operator<(const state &a) const {
		if (x != a.x)	return x < a.x;
		if (y != a.y)	return y < a.y;
		if (log != a.log)	return log < a.log;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (g[i][j] != a.g[i][j])
					return g[i][j] < a.g[i][j];
		return false;
	}
	void print() {
		for (int i = 0; i < n; i++, puts("")) {
			for (int j = 0; j < m; j++) {
				if (i == x && j == y)	printf("!");
				else	printf("%c", g[i][j]);
			}
		}
		printf("log %d\n", log);
		puts("--");
	}
};

int isValid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}
int bfs(state init) {
	state u, v;
	queue<state> Q;
	map<state, int> R;
	int tx, ty;
	Q.push(init), R[init] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int step = R[u];
		if (u.g[u.x][u.y] == 'E')
			return step;	
//		u.print(), getchar();
		for (int i = 0; i < 4; i++) { // traverse
			tx = u.x + dx[i], ty = u.y + dy[i];
			while (isValid(tx, ty) && u.g[tx][ty] != '.') {
				if (u.g[tx][ty] == 'S' || u.g[tx][ty] == 'B' || u.g[tx][ty] == 'E') {
					v = u, v.x = tx, v.y = ty;
					if (R.find(v) == R.end()) {
						R[v] = step + 1;
						Q.push(v);
					}
					break;
				}
				if (i < 2 && u.g[tx][ty] != '-')	break;
				if (i > 1 && u.g[tx][ty] != '|')	break;
				tx += dx[i], ty += dy[i];
			}
		}
		if (u.log == 0) { // pick up
			for (int i = 0; i < 4; i++) {
				tx = u.x + dx[i], ty = u.y + dy[i];
				if (isValid(tx, ty) && ((i < 2 && u.g[tx][ty] == '-') || (i > 1 && u.g[tx][ty] == '|'))) {
					v = u;
					while (isValid(tx, ty) && u.g[tx][ty] != '.') {
						if (u.g[tx][ty] == 'S' || u.g[tx][ty] == 'B' || u.g[tx][ty] == 'E') {
							if (R.find(v) == R.end()) {
								R[v] = step + 1;
								Q.push(v);
							}
							break;
						}
						v.g[tx][ty] = '.', v.log++;
						if (i < 2 && u.g[tx][ty] != '-')	break;
						if (i > 1 && u.g[tx][ty] != '|')	break;
						tx += dx[i], ty += dy[i];						
					}

				}
			}
		} else { // put down.
			for (int i = 0; i < 4; i++) {
				tx = u.x + dx[i], ty = u.y + dy[i];
				if (isValid(tx, ty) && u.g[tx][ty] == '.') {
					int dist = 0;
					while (isValid(tx, ty)) {
						if (u.g[tx][ty] == 'S' || u.g[tx][ty] == 'B' || u.g[tx][ty] == 'E') {
							v = u;
							if (dist == u.log) {
								v.log = 0;
								tx = u.x + dx[i], ty = u.y + dy[i];
								while (isValid(tx, ty) && u.g[tx][ty] == '.') {
									if (u.g[tx][ty] == 'S' || u.g[tx][ty] == 'B' || u.g[tx][ty] == 'E')
										break;
									if (i < 2)	v.g[tx][ty] = '-';
									if (i > 1)	v.g[tx][ty] = '|';
									tx += dx[i], ty += dy[i];
								}
								if (R.find(v) == R.end()) {
									R[v] = step + 1;
									Q.push(v);
								}
							}
							break;
						}
						if (u.g[tx][ty] != '.')	break;
						dist++;
						tx += dx[i], ty += dy[i];
					}

				}
			}
		}
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		state init, u, v;
		for (int i = 0; i < n; i++)
			scanf("%s", init.g[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (init.g[i][j] == 'B')
					init.x = i, init.y = j, init.log = 0;
			}
		}
		int ret = bfs(init);
		printf("%d\n", ret);
	}
	return 0;
}
/*
999
7 11
....S......
....|......
B---S......
...........
...........
...........
....S.S...E
4 4
....
.B.S
.|..
...E
7 11
....S...S..
........|..
B-----S.|.E
......|.|..
......|.S..
......|....
....S-S....
4 4
....
S-B.
....
..E.
*/
