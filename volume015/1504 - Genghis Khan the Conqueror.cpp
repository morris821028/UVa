#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
struct Edge {
	int x, y, c;
	bool operator<(const Edge &e) const {
		return c < e.c;
	}
};
class DisjointSet {
public:
	int parent[MAXN], weight[MAXN];
	void init(int n) {
		for (int i = 0; i <= n; i++)
			parent[i] = i, weight[i] = 1;
	}
	int findp(int x) {
		return parent[x] == x ? x : (parent[x]=findp(parent[x]));
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if (x == y)	return 0;
		if (weight[x] > weight[y])
			parent[y] = x, weight[x] += weight[y];
		else
			parent[x] = y, weight[y] += weight[x];
		return 1;
	}
};

int mst(int n, int m, Edge e[], vector<int> g[]) {
	sort(e, e+m);
	
	DisjointSet d;
	d.init(n);
	int ret = 0;
	for (int i = 0; i < m; i++) {
		if (d.joint(e[i].x, e[i].y)) {
			ret += e[i].c;
			g[e[i].x].push_back(e[i].y);
			g[e[i].y].push_back(e[i].x);
		}
	}
	
	return ret;
}

static int G[MAXN][MAXN], AG[MAXN][MAXN], MG[MAXN][MAXN];
int dfs(int root, int u, int p, const vector<int> g[]) {
	int ret = 0x3f3f3f3f;
	for (auto v : g[u]) {
		if (v == p)
			continue;
		int t = dfs(root, v, u, g);
		AG[u][v] = min(AG[u][v], t);
		ret = min(ret, t);
	}
	if (p != root)
		ret = min(ret, G[root][u]);
	return ret;
}
void alter(int n, int m, Edge e[], vector<int> g[]) {
	for (int i = 0; i < n; i++) {
		memset(G[i], 0x3f, sizeof(G[0][0])*n);
		memset(AG[i], 0x3f, sizeof(AG[0][0])*n);
		memset(MG[i], 0x00, sizeof(MG[0][0])*n);
		for (auto v : g[i])
			MG[i][v] = 1;
	}
	
	for (int i = 0; i < m; i++) {
		int x = e[i].x, y = e[i].y, c = e[i].c;
		G[x][y] = G[y][x] = c;
	}
		
	// find minimum alternative edge
	for (int i = 0; i < n; i++) {
		dfs(i, i, -1, g);
	}
}
int main() {
	int n, m, q;
	static Edge e[MAXN*MAXN];
	static vector<int> g[MAXN];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < m; i++)
			scanf("%d %d %d", &e[i].x, &e[i].y, &e[i].c);
		
		for (int i = 0; i < n; i++)
			g[i].clear();
		int mst_cost = mst(n, m, e, g);
		
		alter(n, m, e, g);
		
		scanf("%d", &q);
		double extra = 0;
		for (int i = 0; i < q; i++) {
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c);
			// if this edge does not belong the edges of MST,
			// , it won't affect the cost
			if (MG[x][y] != 0)
				extra += min(AG[x][y], c) - G[x][y];
		}
		printf("%.4lf\n", mst_cost + (double) extra/q);
	}
	return 0;
}
/*
3 3
0 1 3
0 2 2
1 2 5
3
0 2 3
1 2 6
0 1 6
0 0
*/
