#include <stdio.h> 
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector<int> g[128];
int visited[128];
int A[128], An, color[128];
int used[128];
int dfs(int idx) {
	if (idx == An)
		return 1;
	for (int c = (idx == 0 ? 4 : 1); c <= 4; c++) {
		int u = A[idx], v, ok = 1;
		for (int i = 0; i < g[u].size() && ok; i++) {
			v = g[u][i];
			if (used[v] && color[v] == c)
				ok = 0;
		}
		if (ok) {
			used[u] = 1;
			color[u] = c;
			if (dfs(idx+1))
				return 1;
			used[u] = 0;
		}
	}
	return 0;
}
void bfs(int st) {
	queue<int> Q;
	int u;
	An = 0;
	Q.push(st), visited[st] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		A[An++] = u;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (visited[v] == 0) {
				visited[v] = 1;
				Q.push(v);
			}
		}
	}
	memset(used, 0, sizeof(used));
	dfs(0);
}
int main() {
	char line[128];
	int x, y, n, cases = 0;
	while (scanf("%d", &n) == 1) {
		while (getchar() != '\n'); 
		for (int i = 0; i <= n; i++)
			g[i].clear();
		while (gets(line)) {
			if (line[0] == '\0')
				break;
			sscanf(line, "%d-%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for (int i = 1; i <= n; i++) {
			sort(g[i].begin(), g[i].end());
			g[i].resize(distance(g[i].begin(), unique(g[i].begin(), g[i].end())));
		}
		memset(visited, 0, sizeof(visited));
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) {
				bfs(i);
			}
		}
		if (cases++)	puts("");
		for (int i = 1; i <= n; i++)
			printf("%d %d\n", i, color[i]);
	}
	return 0;
}
/*
8
1-2
3-1
4-5
4-8
1-7
1-4
7-1
2-4
1-8
6-7
2-3
1-5
1-6
7-6
7-8
2-5
7-1
3-4
5-6
7-8
*/
