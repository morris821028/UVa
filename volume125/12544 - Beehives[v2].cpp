#include <stdio.h> 
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm> 
using namespace std;

vector<int> g[512];
int dist[512], parent[512];
int bfs(int st, int &ret) {
	memset(dist, 0, sizeof(dist));
	dist[st] = 1, parent[st] = -1;
	queue<int> Q;
	Q.push(st);
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if(v == parent[u])	continue;
			if(dist[v] == 0) {
				dist[v] = dist[u] + 1;
				parent[v] = u;
				Q.push(v);
			} else {
				ret = min(ret, dist[u] + dist[v] - 1);
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int n, m, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++)
			g[i].clear();
		while(m--) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		int ret = n + 1;
		for(int i = 0; i < n; i++)
			bfs(i, ret);
		printf("Case %d: ", ++cases);
		if(ret == n + 1)
			puts("impossible");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
3
3 3
0 1
1 2
2 0
2 1
0 1
5 6
0 1
1 2
1 3
2 3
0 4
3 4
*/
