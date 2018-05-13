#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 305;
int n, m, g[MAXN][MAXN];
bitset<MAXN*MAXN*7*6> used;
inline int bitpos(int x, int y, int p, int t) {
	return ((x*m+y)*7+p)*6+t;
}
struct Stat {
	int x, y, p, t, d;
	pair<int, int> prev;
	Stat(int x=0, int y=0, int p=0, int t=0):
		x(x), y(y), p(p), t(t) {}
};
int bfs(int sx, int sy, int ex, int ey) {
	if (g[sx][sy] == 0 || g[ex][ey] == 0)
		return -1;
	Stat u(sx, sy, 0, 0);
	u.d = 0;
	if (g[sx][sy] == 1) {
		u.p = 1, u.t = 0, u.prev = {-1, -1};
	} else {
		u.p = g[sx][sy]%10, u.t = g[sx][sy]/10, u.prev = {sx, sy};
	}
	
	used.reset();
	
	queue<Stat> Q;
	Q.push(u);
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		for (int i = 0; i < 4; i++) {
			int tx = u.x + dx[i]*u.p;
			int ty = u.y + dy[i]*u.p;
			if (tx < 0 || ty < 0 || tx >= n || ty >= m || g[tx][ty] == 0)
				continue;
			Stat v(tx, ty, 0, 0);
			v.d = u.d+1;
			if (g[tx][ty] > 1 && make_pair(tx, ty) != u.prev) {
				v.p = g[tx][ty]%10;
				v.t = g[tx][ty]/10;
				v.prev = {tx, ty};
			} else {
				if (u.p > 1 && u.t > 1) {
					v.p = u.p;
					v.t = u.t-1;
					v.prev = u.prev;
				} else {
					v.p = 1;
					v.t = 0;
					v.prev = {-1, -1};
				}
			}
			int bpos = bitpos(v.x, v.y, v.p, v.t);
			if (used[bpos] == 0) {
				if (v.x == ex && v.y == ey)
					return v.d;
				used[bpos] = 1;
				Q.push(v);
			}
		}
	}
	return -1;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		}
		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		
		int ret = bfs(sx, sy, ex, ey);
		
		if (ret != -1)
			printf("%d\n", ret);
		else
			puts("IMPOSSIBLE");
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
8 8
0 1 1 1 1 1 1 1
0 1 0 0 1 13 1 1
0 1 32 1 1 1 0 0
0 1 1 0 1 1 1 0
0 1 1 0 0 0 0 0
0 1 1 1 1 1 1 0
0 1 0 0 1 1 1 0
0 1 1 1 1 1 1 0
1 7
5 4
*/
