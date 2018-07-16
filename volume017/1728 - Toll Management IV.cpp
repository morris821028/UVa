#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 10005;
struct EdgeIn {
	int x, y, w;
	EdgeIn() {}
	EdgeIn(int x, int y, int w):
		x(x), y(y), w(w) {}
} edges[MAXN];

struct Edge {
	int to, i;
	Edge() {}
	Edge(int to, int i):
		to(to), i(i) {}
};

vector<Edge> g[MAXN];
vector<EdgeIn> q;

int to_p[MAXN];
int16_t depth[MAXN], visited[MAXN];
int16_t st_p[MAXN][16], st_w[MAXN][16];
int16_t parent[MAXN];
void dfs(int u, int p, int dep) {
	depth[u] = dep;
	
	for (int i = 1, j = 2; j <= dep; i++, j <<= 1) {
		st_p[u][i] = st_p[st_p[u][i-1]][i-1];
		st_w[u][i] = max(st_w[u][i-1], st_w[st_p[u][i-1]][i-1]);
	}
	
	for (auto e : g[u]) {
		if (depth[e.to] != -1)
			continue;
		st_p[e.to][0] = u;
		st_w[e.to][0] = edges[e.i].w;
		to_p[e.to] = e.i;
		dfs(e.to, u, dep+1);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(st_p, -1, sizeof(st_p));
	dfs(1, -1, 0);
}


static inline int log2int(int32_t x) {
	return 32 - __builtin_clz(x); 
}

int max_path(int x, int y) {
	if (x == y)
		return 0;
	if (depth[x] < depth[y])
		swap(x, y);
	int16_t ret = SHRT_MIN;
	if (depth[x] > depth[y]) {
		int diff = depth[x] - depth[y];
		for (int i = 0; diff; i++) {
			if ((diff>>i)&1) {
				ret = max(ret, st_w[x][i]);
				x = st_p[x][i];
				diff ^= 1<<i;
			}
		}
	}
	
	if (x != y) {
		int h = log2int(depth[x]) + 1;
		for (int i = h; i >= 0; i--) {
			if (st_p[x][i] != st_p[y][i]) {
				ret = max(ret, st_w[x][i]);
				ret = max(ret, st_w[y][i]);
				x = st_p[x][i];
				y = st_p[y][i];
			}
		}
		ret = max(ret, st_w[x][0]);
		ret = max(ret, st_w[y][0]);
	}
	
	return ret;
}

int get_lca(int x, int y) {
	if (x == y)
		return x;
	if (depth[x] < depth[y])
		swap(x, y);
	if (depth[x] > depth[y]) {
		int diff = depth[x] - depth[y];
		for (int i = 0; diff; i++) {
			if ((diff>>i)&1) {
				x = st_p[x][i];
				diff ^= 1<<i;
			}
		}
	}
	
	if (x != y) {
		int h = log2int(depth[x]) + 1;
		for (int i = h; i >= 0; i--) {
			if (st_p[x][i] != st_p[y][i]) {
				x = st_p[x][i];
				y = st_p[y][i];
			}
		}
		x = st_p[x][0];
	}
	
	return x;
}

int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}

int64_t min_path(int u, int p, int w) {
	int v = findp(u);
	if (v == p)
		return 0;
	int next = parent[u] == v ? st_p[u][0] : v;
	int64_t ret = 0;
	if (!visited[u]) {
		visited[u] = 1;
		
		int64_t i = to_p[u];
		const int a = w - st_w[u][0];
		const int b = -1;
		ret += i*a + i*i*b;
	}
	
	parent[u] = p;
	ret += min_path(next, p, w);
	return ret;
}

int64_t solve(int n) {
	sort(q.begin(), q.end(), [](const EdgeIn &x, const EdgeIn &y) {
		return x.w < y.w;
	});
	
	int64_t ret = 0;
	for (int i = 0; i <= n; i++)
		parent[i] = i, visited[i] = 0;
	for (int i = 0; i < q.size(); i++) {
		int lca = get_lca(q[i].x, q[i].y);
		lca = findp(lca);
		ret += min_path(q[i].x, lca, q[i].w);
		ret += min_path(q[i].y, lca, q[i].w);
	}
	
	for (int u = 2; u <= n; u++)  {
		if (visited[u] == 0) {
			int64_t i = to_p[u];
			const int a = -1;
			const int b = -1;
			ret += i*a + i*i*b;
		}
	}
	return ret;
}

int main() {
	int testcase, cases = 0;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);

		for (int i = 0; i <= n; i++)
			g[i].clear();
		q.clear();
		
		for (int i = 1; i <= m; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			if (i < n) {
				edges[i] = EdgeIn(x, y, w);
				g[x].push_back(Edge(y, i));
				g[y].push_back(Edge(x, i));
			} else {
				q.push_back(EdgeIn(x, y, w));
			}
		}
		
		build(n);
		
		int64_t ret = 0;
		
		// for non-tree edge
		for (int i = 0; i < q.size(); i++) {
			int64_t j = i+n;
			const int a = -1;
			const int b = q[i].w - max_path(q[i].x, q[i].y);
			ret += j * a + j*j * b;
		}
		
		// for tree edge
		ret += solve(n);
		
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
3  3
1  2  5
2  3  7
1  3  10
4  5
1  3  1
3  4  2
1  2  3
1  4  4
2  4  5
*/
