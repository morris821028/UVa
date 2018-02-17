#include <bits/stdc++.h>
using namespace std;
const int MAXN = 51;
struct Rect {
	int lx, ly, rx, ry;
	void read() {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
	}
} rect[MAXN];
vector<int> X, Y;
char g[MAXN*4][MAXN*4];
int decX(int x) { return lower_bound(X.begin(), X.end(), x) - X.begin(); }
int decY(int y) { return lower_bound(Y.begin(), Y.end(), y) - Y.begin(); }
void build(int n) {
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) {
		X.push_back(rect[i].lx), X.push_back(rect[i].rx);
		X.push_back(rect[i].lx-1), X.push_back(rect[i].rx+1);
		Y.push_back(rect[i].ly), Y.push_back(rect[i].ry);
		Y.push_back(rect[i].ly-1), Y.push_back(rect[i].ry+1);
	}
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	for (int i = 0; i < n; i++) {
		int lx, ly, rx, ry;
		lx = decX(rect[i].lx), rx = decX(rect[i].rx);
		ly = decY(rect[i].ly), ry = decY(rect[i].ry);
		for (int p = lx; p <= rx; p++)	// contain right boundary
			g[p][ly] = g[p][ry] = 1;
		for (int q = ly; q <= ry; q++)
			g[lx][q] = g[rx][q] = 1;
	}
}
int bfs(int sx, int sy, int ex, int ey) {
	vector<pair<int, int>> q, q2;
	char used[MAXN*4][MAXN*4] = {};
	static int dx[] = {0, 0, 1, -1};
	static int dy[] = {1, -1, 0, 0};
	int ret = 0;
	used[sx][sy] = 1;
	q.push_back({sx, sy});
	for (; !q.empty();) {
		q2.clear();
		while (!q.empty()) {
			auto u = q.back();
			q.pop_back();
			for (int i = 0; i < 4; i++) {
				int tx = u.first+dx[i], ty = u.second+dy[i];
				while (tx >= 0 && ty >= 0 && tx <= X.size() && ty <= Y.size()) {
					if (g[tx][ty])
						break;
					if (used[tx][ty] == 0) {
						used[tx][ty] = 1;
						if (tx == ex && ty == ey)
							return ret;
						q2.push_back({tx, ty});
					}
					tx += dx[i], ty += dy[i];
				}
			}
		}
		q.swap(q2), ret++;
	}
	return -1;
}
int main() {
	int testcase, cases = 0, n, q;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			rect[i].read();
		scanf("%d", &q);
		printf("Labyrinth #%d\n", ++cases);
		for (int i = 0; i < q; i++) {
			int sx, sy, ex, ey;
			int dsx, dsy, dex, dey;
			scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
			X.clear(), Y.clear();
			X.push_back(sx), X.push_back(ex);
			Y.push_back(sy), Y.push_back(ey);
			build(n);
			dsx = decX(sx), dsy = decY(sy);
			dex = decX(ex), dey = decY(ey);
			int ret = bfs(dsx, dsy, dex, dey);
			if (ret >= 0)
				printf("%d\n", ret);
			else
				puts("Impossible.");
		}
	}
	return 0;
}
/*
2
0
2
10 10 20 20
10 10 10 20
1
10 10 100 100
2
9 10 101 10
1 1 1000 1000

*/
