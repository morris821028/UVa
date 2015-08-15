#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 100005;
const int MAXLOGN = 17;
struct Event {
	char s[8];
	int x, y;
	void read() {
		scanf("%s %d %d", s, &x, &y);
	}
};
int fa[MAXLOGN][MAXN], visited[MAXN], dep[MAXN];
int parent[MAXN];
vector<int> g[MAXN];
void dfs(int u) {
	visited[u] = 1;
	for (auto v : g[u]) {
		fa[0][v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int LCA(int x, int y) {
	if (dep[x] < dep[y])	swap(x, y);
	int d = dep[x] - dep[y];
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if ((d>>i)&1) {
			d -= 1<<i;
			x = fa[i][x];
		}
	}
	if (x == y)	return x;
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if (fa[i][x] != fa[i][y]) {
			x = fa[i][x], y = fa[i][y];
		}
	}
	return fa[0][x];
}
void sim(int x, int y) {
	int rx, ry, lca;
	rx = findp(x), ry = findp(y);
	if (rx != ry) {
		puts("-1");
		return ;
	}
	lca = LCA(x, y);
	int a = (dep[lca]-dep[rx]+1)*2, b = dep[x]+dep[y]-dep[rx]*2+2, g;
	g = __gcd(a, b), a /= g, b /= g;
	printf("%d/%d\n", a, b);
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			g[i].clear(), visited[i] = 0, parent[i] = i;
		vector<Event> e(m);
		for (int i = 0; i < m; i++) {
			e[i].read();
			if (e[i].s[0] == 'n')
				g[e[i].y].push_back(e[i].x);
		}
		
		memset(visited, 0, (n+1) * sizeof(visited[0]));
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0)
				dfs(i);
		}
		
		for (int i = 1; i < MAXLOGN; i++)
			for (int j = 1; j <= n; j++)
				fa[i][j] = fa[i-1][fa[i-1][j]];
				
		for (int i = 0; i < m; i++) {
			if (e[i].s[0] == 'n') {
				parent[e[i].x] = e[i].y;
			} else {
				sim(e[i].x, e[i].y);
			}
		}
	}
	return 0;
}
