#include <bits/stdc++.h>
using namespace std;
namespace Edmonds {
	const int MAXN = 505;
	vector<int> g[MAXN];
	int parent[MAXN], match[MAXN], belong[MAXN], state[MAXN];
	int n;
	// virtual node label: 0
	// state: -1 not used, 0: even, 1: odd vertex
	int lca(int u, int v) {
		static int cases = 0, used[MAXN] = {};
		for (++cases; ; swap(u, v)) {
			if (u == 0)
				continue;
			if (used[u] == cases)
				return u;
			used[u] = cases;
			u = belong[parent[match[u]]];
		}
	}
	void flower(int u, int v, int l, queue<int> &q) {
		while (belong[u] != l) {
			parent[u] = v, v = match[u];
			if (state[v] == 1)
				q.push(v), state[v] = 0;
			belong[u] = belong[v] = l, u = parent[v];
		}
	}
	bool bfs(int u) {
		for (int i = 0; i <= n; i++)
			belong[i] = i;
		memset(state, -1, sizeof(state[0])*(n+1));
		queue<int> q;
		q.push(u), state[u] = 0;
		while (!q.empty()) {
			u = q.front(), q.pop();
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i];
				if (state[v] == -1) {
					parent[v] = u, state[v] = 1;
					if (match[v] == 0) {
						for (int prev; u; v = prev, u = parent[v]) {
							prev = match[u];
							match[u] = v;
							match[v] = u;
						}
						return 1;
					}
					q.push(match[v]), state[match[v]] = 0;
				} else if (state[v] == 0 && belong[v] != belong[u]) {
					int l = lca(u, v);
					flower(v, u, l, q);
					flower(u, v, l, q);
				}
			}
		}
		return 0;
	}
	int bloosom() {
		memset(parent, 0, sizeof(parent[0])*(n+1));
		memset(match, 0, sizeof(match[0])*(n+1));
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			if (match[i] == 0 && bfs(i))
				ret++;
		}
		return ret;
	}
	void addEdge(int x, int y) {
		g[x].push_back(y), g[y].push_back(x);
	}
	void init(int n) {
		Edmonds::n = n;
		for (int i = 0; i <= n; i++)
			g[i].clear();
	}
}
using namespace Edmonds;
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		n = 1<<n;
		vector<int> A;
		int w[128][128];
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				scanf("%d", &w[i][j]);
				A.push_back(w[i][j]);
			}
		}
		
		sort(A.begin(), A.end());
		A.resize(unique(A.begin(), A.end()) - A.begin());
		int l = 0, r = A.size()-1, mid;
		int ret = 0;
		while (l <= r) {
			mid = (l + r)/2;
			int least = A[mid];
			init(n);
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					if (w[i][j] >= least)
						addEdge(i+1, j+1);
				}
			}
			int ff = bloosom();
			if (ff >= n/2)
				l = mid+1, ret = least;
			else
				r = mid-1;
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
1

2
300 300 300
100 200
100
*/
