#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
vector<int> g[1024];
int bfs(int n) {
	int visited[1024] = {};
	int u, v, ret = 0;
	queue<int> Q;
	Q.push(0), visited[0] = 1;
	while(!Q.empty()) {
		u = Q.front(), Q.pop();
		for(int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if(visited[v] == 0) {
				visited[v] = visited[u] + 1;
				ret += visited[u];
				Q.push(v);
			}
		}
	}
	return ret;
}
int main() {
	int n, m, x, y;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		for(int i = 0; i < n; i++)
			g[i].clear();
		int size = 0, eflag = 0;
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			if(x >= 0 && x < n && y >= 0 && y < n) {
				g[x].push_back(y);
				g[y].push_back(x);
			} else {
				eflag = 1;
			}
		}
		for(m = 0; (1<<m) < n; m++);
		for(int i = 0; i < n; i++)
			if(g[i].size()%m)
				eflag = 1;
		if((n&(-n)) != n || eflag) {
			puts("NO");
			continue;
		}
		int ret = 0, ac = 0;
		for(int i = 0; i < n; i++)
			ret += bfs(i);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				int t = i^j;
				ac += __builtin_popcount(t);
			}
		}
		puts(ret == ac ? "YES" : "NO");
	}
	return 0;
}
