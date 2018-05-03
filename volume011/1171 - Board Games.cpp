#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 305;
vector<pair<int, int>> g[MAXN];
int64_t dist[MAXN];
const int64_t LLINF = 1LL<<60;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		int st, ed;
		scanf("%d", &n);
		scanf("%d %d", &st, &ed);
		scanf("%d", &m);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			g[u].push_back({v, c});
		}
		
		for (int i = 0; i < n; i++)
			dist[i] = LLINF;
		dist[st] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (auto e : g[j]) {
					if (dist[e.first] > dist[j] + e.second)
						dist[e.first] = dist[j] + e.second;
				}
			}
		}
		const int64_t ret = dist[ed];
		
		if (ret != LLINF)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (auto e : g[j]) {
					if (dist[e.first] > dist[j] + e.second)
						dist[e.first] = dist[j] + e.second;
				}
			}
			if (dist[ed] < ret)
				break;
		}
		
		if (ret == dist[ed] && dist[ed] != LLINF)
			printf("%lld\n", ret);
		else
			puts("infinity");
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2

4
0 3
4
0 1 5
0 2 7
2 1 -3
1 3 2

4
0 3
3
0 1 5
0 2 7
2 1 -3
*/
