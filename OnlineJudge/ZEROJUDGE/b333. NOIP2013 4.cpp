#include <bits/stdc++.h>
using namespace std;
vector< pair<int, int> > g[4096];
int main() {
	int n, m, s, a[1024];
	while (scanf("%d %d", &n, &m) == 2) {
		int N = n+m+10, vr = n;
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d", &s);
			for (int j = 0; j < s; j++)
				scanf("%d", &a[j]);
			int st = a[0], ed = a[s-1];
			vr++;
			vector<int> P, Q;
			for (int j = st, k = 0; j <= ed; j++) {
				if (j == a[k])
					P.push_back(j), k++;
				else
					Q.push_back(j);
			}
			if (P.size() == 0 || Q.size() == 0)
				continue;
			for (auto &x : P)
				g[vr].push_back({x, 1});
			for (auto &x : Q)
				g[x].push_back({vr, 0});
		}
		
		int indeg[4096] = {}, dist[4096] = {}; 
		int u, v, ret = 0;
		queue<int> Q;
		for (int i = 1; i <= vr; i++) {
			for (auto &x : g[i])
				indeg[x.first]++;
		}
		for (int i = 1; i <= vr; i++)
			if (indeg[i] == 0)
				Q.push(i);
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			for (auto &x : g[u]) {
				dist[x.first] = max(dist[x.first], dist[u] + x.second);
				if (--indeg[x.first] == 0)
					Q.push(x.first);
			}
			ret = max(ret, dist[u]);
		}
		printf("%d\n", ret+1);
	}
	return 0;
}
