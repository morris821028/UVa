#include <bits/stdc++.h> 
using namespace std;

// advanced: 1708 - Wire Crossing

struct Seg {
	int lx, ly, rx, ry;
	Seg(int lx=0, int ly=0, int rx=0, int ry=0):
		lx(lx), ly(ly), rx(rx), ry(ry) {}
};
const int MAXN = 512;
int sx, sy, ex, ey, n;
Seg segs[MAXN];
vector<int> X, Y;
int N, M;
char g[MAXN][MAXN];
int Xidx(int x) {
	return lower_bound(X.begin(), X.end(), x)-X.begin()+1;
}
int Yidx(int y) {
	return lower_bound(Y.begin(), Y.end(), y)-Y.begin()+1;
}
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int bfs() {
	X.clear(), Y.clear();
	X.reserve(n*2+2), Y.reserve(n*2+2);
	X.push_back(sx), X.push_back(ex);
	Y.push_back(sy), Y.push_back(ey);
	for (int i = 0; i < n; i++) {
		X.push_back(segs[i].lx), X.push_back(segs[i].rx);
		Y.push_back(segs[i].ly), Y.push_back(segs[i].ry);
	}
	sort(X.begin(), X.end());
	X.resize(unique(X.begin(), X.end())-X.begin());
	sort(Y.begin(), Y.end());
	Y.resize(unique(Y.begin(), Y.end())-Y.begin());

	N = X.size()+2, M = Y.size()+2;
	for (int i = 0; i < N; i++)
		memset(g[i], 0, sizeof(g[i][0])*M);
	sx = Xidx(sx), ex = Xidx(ex);
	sy = Yidx(sy), ey = Yidx(ey);
	for (int i = 0; i < n; i++) {
		segs[i].lx = Xidx(segs[i].lx), segs[i].rx = Xidx(segs[i].rx);
		segs[i].ly = Yidx(segs[i].ly), segs[i].ry = Yidx(segs[i].ry);
		if (segs[i].lx == segs[i].rx) {
			for (int j = segs[i].ly; j < segs[i].ry; j++) {
				g[segs[i].lx][j] |= 1;
				g[segs[i].lx-1][j] |= 2;
			}
		} else {
			for (int j = segs[i].lx; j < segs[i].rx; j++) {
				g[j][segs[i].ly] |= 4;
				g[j][segs[i].ly-1] |= 8;
			}
		}
	}
	vector<pair<int, int>> q, q2;
	static bitset<MAXN*MAXN*4> R;
	R.reset();
	q.push_back({sx, sy});
	for (int ret = 0; !q.empty(); ret++) {
		q2.clear();
		while (!q.empty()) {
			auto u = q.back(); q.pop_back();
			int rpos = u.first*M+u.second;
			if (u.first == ex && u.second == ey)
				return ret;
			if (R[rpos])
				continue;
			R[rpos] = 1;
			int cond = g[u.first][u.second];
			for (int i = 0; i < 4; i++) {
				int tx = u.first+dx[i];
				int ty = u.second+dy[i];
				if (tx < 0 || ty < 0 || tx >= N || ty >= M)
					continue;
				int spos = tx*N+ty;
				if (R[spos])
					continue;
				if ((cond>>i)&1) {
					q2.push_back({tx, ty});
				} else {
					q.push_back({tx, ty});
				}
			}
		}
		q.swap(q2);
	}
	assert(false);
	return -1;
}

int main() {
	int cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n;  i++) {
			int lx, ly, rx, ry;
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			if (lx > rx)	swap(lx, rx);
			if (ly > ry)	swap(ly, ry);
			segs[i] = Seg(lx, ly, rx, ry);
		}
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

		int ret = bfs();

		printf("City %d\n", ++cases);
		printf("Peter has to cross %d streets\n", ret);
	}
	return 0;
}
/*
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0
*/
