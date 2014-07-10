#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[128];
int visited[128] = {};
int path[256], f = 0, target = 0;
void dfs(int u, int p, int dep) {
	if(visited[u] > 2) {
		f = 2;
		return;
	}
	if(u == target) {
		printf("%d", path[0]);
		for(int i = 1; i < dep; i++)
			printf(" %d", path[i]);
		puts("");
		f = 1;
		return;
	}
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(v == p)	continue;
		path[dep] = v;
		visited[v]++;
		dfs(v, u, dep + 1);
		if(f)	return;
	}
}
int main() {
	int testcase, cases = 0;
	int n, m, s, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &n, &m, &s);
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}	
		printf("Case #%d:\n", ++cases);
		for(int i = 0; i < n; i++)
			sort(g[i].begin(), g[i].end());
		for(int i = 0; i < n; i++) {
			f = 0, target = i, path[0] = s, visited[s] = 1;
			memset(visited, 0, sizeof(visited));
			dfs(s, -1, 1);
			if(f != 1)
				puts("No drive.");
		}
		puts("");
	}
	return 0;
}
