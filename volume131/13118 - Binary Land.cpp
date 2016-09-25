#include <bits/stdc++.h>
using namespace std;

struct State {
	int lx, ly, gx, gy;
	State(int lx=0, int ly=0, int gx=0, int gy=0):
		lx(lx), ly(ly), gx(gx), gy(gy) {
	}
};
int R, C;
char g[42][50];
int lx, ly, gx, gy, mx, my;
char visited[42][42][42][42];
int bfs() {
	memset(visited, 0, sizeof(visited));
	queue<State> Q;
	queue<int> DQ;
	visited[lx][ly][gx][gy] = 1;
	Q.push(State(lx, ly, gx, gy)), DQ.push(0);
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	const int ox[] = {0, 0, 1, -1};
	const int oy[] = {-1, 1, 0, 0};
	if (lx == gx && ly == gy && lx == mx && ly == my)
		return 0;
	while (!Q.empty()) {
		State u = Q.front();
		int d = DQ.front();
		Q.pop(), DQ.pop();
		for (int i = 0; i < 4; i++) {
			State v = u;
			int tx, ty;
			tx = v.lx + dx[i], ty = v.ly + dy[i];
			if (tx > 0 && ty > 0 && tx <= R && ty <= C
				&& g[tx][ty] == '.')
				v.lx = tx, v.ly = ty;
			tx = v.gx + ox[i], ty = v.gy + oy[i];
			if (tx > 0 && ty > 0 && tx <= R && ty <= C
				&& g[tx][ty] == '.')
				v.gx = tx, v.gy = ty;
			if (v.lx == v.gx && v.ly == v.gy && v.lx == mx && v.ly == my)
				return d+1;
			if (!visited[v.lx][v.ly][v.gx][v.gy]) {
				visited[v.lx][v.ly][v.gx][v.gy] = 1;
				visited[v.gx][v.gy][v.lx][v.ly] = 1;
				Q.push(v), DQ.push(d+1);
			}
		}
	}
	return -1;
}
int main() {
	while (scanf("%d %d", &R, &C) == 2) {
		scanf("%d %d %d %d %d %d", &mx, &my, &gx, &gy, &lx, &ly);
		for (int i = 1; i <= R; i++)
			scanf("%s", g[i]+1);
			
		int ret = bfs();
		if (ret == -1)
			puts("NO LOVE");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
10 15
1 8 10 9 10 7
...............
.###.###.###.##
##.#.#.###.#.#.
.......#.......
.#####.#.#####.
.......#.......
##.#.#.#.#.#.##
.......#.......
.#############.
.......#.......
3 3
1 2 3 2 3 2
...
.#.
...
3 3
1 2 3 2 3 2
...
###
...
3 3
3 2 3 2 3 2
...
###
...
*/

