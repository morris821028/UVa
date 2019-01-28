#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;
struct Pt {
	int x, y;
	Pt() {}
	Pt(int x, int y):x(x), y(y) {}
	void read() {
		scanf("%d %d", &x, &y);
	}
	bool operator<(const Pt &o) const {
		if (x != o.x)	return x < o.x;
		return y < o.y; 
	}
} pt[MAXN], gt[MAXN], st, ed;
vector<int> X, Y;
int8_t g[MAXN][MAXN];

Pt to_grid(Pt p) {
	int x = lower_bound(X.begin(), X.end(), p.x) - X.begin();
	int y = lower_bound(Y.begin(), Y.end(), p.y) - Y.begin();
	return Pt(x, y);
}


const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
int full(int x, int y) {
	if (x < 0 || x >= X.size() || y < 0 || y >= Y.size())
		return 0;
	return g[x][y];
}
int valid(Pt p, int d) {
	if (d == 0)
		return full(p.x, p.y) || full(p.x, p.y-1);
	if (d == 1)
		return full(p.x-1, p.y) || full(p.x-1, p.y-1);
	if (d == 2)
		return full(p.x, p.y) || full(p.x-1, p.y);
	if (d == 3)
		return full(p.x, p.y-1) || full(p.x-1, p.y-1);
	assert(false);
}
int cost(Pt p, Pt q) {
	return abs(X[p.x]-X[q.x]) + abs(Y[p.y]-Y[q.y]);
}
int dist[MAXN][MAXN];
int path(Pt st, Pt ed) {
	set<pair<int, Pt>> pQ;
	pQ.insert({0, st}), dist[st.x][st.y] = 0;
	while (!pQ.empty()) {
		auto pu = *pQ.begin(); pQ.erase(pQ.begin());
		Pt u = pu.second;
		if (u.x == ed.x && u.y == ed.y)
			return dist[u.x][u.y];
		for (int i = 0; i < 4; i++) {
			if (!valid(u, i))
				continue;
			Pt v(u.x + dx[i], u.y + dy[i]);
			int w = cost(u, v);
			if (dist[v.x][v.y] > dist[u.x][u.y] + w) {
				if (dist[v.x][v.y] != INF)
					pQ.erase(pQ.find({dist[v.x][v.y], v}));
				dist[v.x][v.y] = dist[u.x][u.y] + w;
				pQ.insert({dist[v.x][v.y], v});
			}
		}
	}
	return -1;
}

int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			pt[i].read();
		st.read();
		ed.read();
		
		X.clear(), Y.clear();
		X.push_back(st.x), X.push_back(ed.x);
		Y.push_back(st.y), Y.push_back(ed.y);
		for (int i = 0; i < n; i++)
			X.push_back(pt[i].x), Y.push_back(pt[i].y);
		
		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());
		sort(Y.begin(), Y.end());
		Y.erase(unique(Y.begin(), Y.end()), Y.end());
		
		for (int i = 0; i < n; i++)
			gt[i] = to_grid(pt[i]);
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++)
				g[i][j] = 0;
		}
		for (int i = n-1, j = 0; j < n; i = j++) {
			if (gt[i].y == gt[j].y) {
				int l = min(gt[i].x, gt[j].x);
				int r = max(gt[i].x, gt[j].x);
				for (int k = l; k < r; k++)
					g[k][gt[i].y] ^= 1;
			}
		}
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0, v = 0; j < Y.size(); j++) {
				v ^= g[i][j];
				g[i][j] = v;
			}
		}
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++)
				dist[i][j] = INF;
		}

		int ret = path(to_grid(st), to_grid(ed));
		printf("Castle %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
10
9 6
9 2
12 2
12 9
2 9
2 1
8 1
8 3
4 3
4 6
11 5
3 1
5
0 0
0 1
0 2
2 2
2 0
2 2
1 1
0
*/
