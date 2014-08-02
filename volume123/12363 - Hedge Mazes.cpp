#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[131072];

int visited[131072], depth[131072];
vector< pair<int, int> > bridge;
int findBridge(int u, int p, int dep) {
	visited[u] = 1, depth[u] = dep;
	int back = 0x3f3f3f3f;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(v == p)	continue;
		if(!visited[v]) {
			int b = findBridge(v, u, dep+1);
			if(b > dep) {
				bridge.push_back(make_pair(u, v));
			}
			back = min(back, b);
		} else {
			back = min(back, depth[v]);
		}
	}
	return back;
}

int rank[131072], parent[131072];
int findp(int x) {
	return parent[x] == x ? x : parent[x]=findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if(x == y)	return 0;
	if(rank[x] > rank[y])
		rank[x] += rank[y], parent[y] = x;
	else
		rank[y] += rank[x], parent[x] = y;
}
int main() {
	int n, m, q, x, y;
	while(scanf("%d %d %d", &n, &m, &q) == 3 && n+m) {
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
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
		
		for(int i = 0; i < n; i++)
			rank[i] = 1, parent[i] = i;
		for(int i = 0; i < bridge.size(); i++)
			joint(bridge[i].first, bridge[i].second);
		for(int i = 0; i < q; i++) {
			scanf("%d %d", &x ,&y);
			x--, y--;
			puts(findp(x) == findp(y) ? "Y" : "N");
		}
		puts("-");
	}
	return 0;
}
