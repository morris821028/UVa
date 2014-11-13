#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[32767];

int visited[32767], depth[32767];
vector< pair<int, int> > bridge;
int findBridge(int u, int p, int dep) {
	visited[u] = 1, depth[u] = dep;
	int back = 0x3f3f3f3f;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(v == p)	continue;
		if(!visited[v]) {
			int b = findBridge(v, u, dep+1);
			if(b > dep)
				bridge.push_back(make_pair(u, v));
			back = min(back, b);
		} else {
			back = min(back, depth[v]);
		}
	}
	return back;
}
int main() {
	int n, m, q, x, y;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		bridge.clear();
		memset(visited, 0, sizeof(visited));
		for(int i = 0; i < n; i++) {
			if(!visited[i]) {
				findBridge(i, -1, 0);
			}
		}
		for (int i = 0; i < bridge.size(); i++)
			if (bridge[i].first > bridge[i].second)
				swap(bridge[i].first, bridge[i].second);
		sort(bridge.begin(), bridge.end());
		printf("%d", bridge.size());
		for (int i = 0; i < bridge.size(); i++)
			printf(" %d %d", bridge[i].first, bridge[i].second);
		puts("");
	}
	return 0;
}
