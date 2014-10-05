#include <stdio.h> 
#include <string.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<int> g[1024];
set<int> A[1024];
int used[1024];
int instk[1024];
int dfs(int u) {
	used[u] = 1, instk[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (instk[v])
			return 1;
		if (!used[v]) {
			if(dfs(v))
				return 1;
			A[u].insert(A[v].begin(), A[v].end());
			if (A[u].size() > 1)
				return 1;
		}
	}
	if (g[u].size() == 0)
		A[u].insert(u);
	instk[u] = 0;
	return A[u].size() > 1;
}
int main() {
	int n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear(), used[i] = 0, A[i].clear(), instk[i] = 0;
		int indeg[1024] = {};
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			indeg[y]++;
		}
		
		int err = 0;
		for (int i = 0; i < n && !err; i++) {
			if (used[i] == 0 && indeg[i] == 0)
				err |= dfs(i);
		}
		for (int i = 0; i < n; i++) // cycle
			if (used[i] == 0)
				err = 1;
		printf("%d\n", !err);
	}
	return 0;
}
/*
3 2
0 1
1 2
2 2
0 1
0 1
2 2
0 1
1 0
3 2
0 1
0 2
0 0
*/
