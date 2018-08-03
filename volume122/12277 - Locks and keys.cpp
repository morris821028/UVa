#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

struct Edge {
	int to, l;
	Edge() {}
	Edge(int to, int l):
		to(to), l(l) {}
} edges[MAXN];

int key_pos[MAXN];
vector<Edge> g[MAXN];

int8_t pass[MAXN];
int8_t ulock[MAXN];
int8_t visited[MAXN];
Edge parent[MAXN];
int dfs(int u, int ed) {
	if (u == ed)
		return 1;
	visited[u] = 1;
	for (auto e : g[u]) {
		if (visited[e.to])
			continue;
		parent[e.to] = Edge(u, e.l);
		if (dfs(e.to, ed))
			return 1;
	}
	return 0;
}

void path(int st, int ed, list<Edge> &ret) {
	memset(visited, 0, sizeof(visited));
	dfs(ed, st);
	while (st != ed) {
		ret.push_back(Edge(st, parent[st].l));
		st = parent[st].to;
	}
}

int unlock_path(int st, int ed, list<Edge> &ret) {
	path(st, ed, ret);
	
	auto prev = ret.begin();
	for (auto it = ret.begin(); it != ret.end(); ) {
		if (it->l < 0 || pass[it->l]) {
			it++;
		} else {
			int pos = key_pos[it->l], stop = it->to;
			if (ulock[it->l])	return 1;
			ulock[it->l] = 1;
			list<Edge> a, b;
			if (unlock_path(prev->to, pos, a))	return 1;
			if (unlock_path(pos, stop, b))	return 1;
			pass[it->l] = 1;
			
			b.splice(b.begin(), a);
			ret.erase(prev, it);
			ret.splice(it, b);
			prev = ++it;
		}
	}
	return 0;
}

void solve(int st, int ed, int n) {
	memset(pass, 0, sizeof(pass));
	memset(ulock, 0, sizeof(ulock));
	list<Edge> path;
	int error = unlock_path(st, ed, path);
	if (error) {
		puts("Impossible");
		return ;
	}
	
	printf("%d:", path.size());
	for (auto e : path)
		printf(" %d", e.to);
	printf(" %d\n", ed);
}

int main() {
	int n, m, st, ed;
	while (scanf("%d %d %d %d", &n, &m, &st, &ed) == 4 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
			
		for (int i = 0; i < m; i++)
			scanf("%d", &key_pos[i]);
		
		for (int i = 0; i < n-1; i++) {
			int a, b, l;
			scanf("%d %d %d", &a, &b, &l);
			g[a].push_back(Edge(b, l));
			g[b].push_back(Edge(a, l));
		}
		
		solve(st, ed, n);
	}
	return 0;
}
/*
1  0  0  0

3  1  0  2
1
0  1  -1
0  2  0

3  2  0  2
1  2
0  1  1
0  2  0

5  3  0  4
2  0  3
0  1  0
0  2  -1
1  3  1
2  4  2

0  0  0  0
*/
