#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
struct edge {
	int x, y, s;
	long long w;
	edge(int a=0, int b=0, long long c=0, int d=0):
		x(a), y(b), w(c), s(d) {}
};
vector<edge> g[32767];

int visited[32767], depth[32767], back[32767];
vector<edge> bridge;
int findBridge(int u, int p, int dep) {
	visited[u] = 1, depth[u] = dep;
	back[u] = 0x3f3f3f3f;
	int sz = 1, t;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].y;
		if(v == p)	continue;
		if(!visited[v]) {
			t = findBridge(v, u, dep+1);
			sz += t;
			if(back[v] > dep)
				bridge.push_back(edge(u, v, g[u][i].w, t));
			back[u] = min(back[u], back[v]);
		} else {
			back[u] = min(back[u], depth[v]);
		}
	}
	return sz;
}

vector<edge> tree[32767];	
long long node_w[32767], place_w[32767];
int dfs(int u, long long mx_w, int p, long long p_w) {
	visited[u] = 1;
	for (int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i].y;
		if (visited[v] == 0) {
			if (!dfs(v, mx_w, u, tree[u][i].w))
				return 0;
		}
	}
	if (place_w[u] + p_w <= mx_w)
		place_w[u] += p_w;
	else
		place_w[p] += p_w;
	if (place_w[u] > mx_w)
		return 0;
	return 1;
		
}
int check(long long mx_w, int n) {
	for (int i = 1; i <= n; i++)
		visited[i] = 0, place_w[i] = node_w[i];
	int ok = 1;
	for (int i = 1; i <= n && ok; i++) {
		if (visited[i] == 0) {
			ok &= dfs(i, mx_w, 0, 0);
		}
	}
//	printf("check %d ok %d\n", mx_w, ok);
	return ok;
}
int main() {
	int testcase, cases = 0, n, m, x, y, w;

	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		
		long long sum = 0, low_w = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &node_w[i]);
			g[i].clear(), tree[i].clear();
			sum += node_w[i], low_w = max(low_w, node_w[i]);
		}
		
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(edge(x, y, w));
			g[y].push_back(edge(y, x, w));
		}
		
		memset(visited, 0, sizeof(visited));
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) {
				bridge.clear();
				int comp_size = findBridge(i, -1, 0);
				for (int j = 0; j < bridge.size(); j++) {
					long long N = (long long) bridge[j].s * (comp_size - bridge[j].s);
					tree[bridge[j].x].push_back(edge(bridge[j].x, bridge[j].y, bridge[j].w * N));
					tree[bridge[j].y].push_back(edge(bridge[j].y, bridge[j].x, bridge[j].w * N));
					sum += bridge[j].w * N;
//					printf("%d %d - %d\n", bridge[j].x, bridge[j].y, bridge[j].w * N);
				}
			}
		}
		
		// binary search answer
		long long l = low_w, r = sum, mid, ret;
		while (l <= r) {
			mid = (l + r)/2;
			if (check(mid, n))
				r = mid - 1, ret = mid;
			else
				l = mid + 1;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
3
2 1
5 10
1 2 10

6 6
10 20 30 40 50 60
1 2 1
2 3 1
1 3 1
1 4 6
1 5 6
4 6 2

3 1
10 20 30
2 3 1

9999
3 3
4 5 6
1 2 1
2 3 1
3 1 1
*/
