#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1024;
int A[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p, int ret[]) {
	ret[0] = 0, ret[1] = A[u];
	for (int i = 0, v; i < g[u].size(); i++) {
		v = g[u][i];
		if (v == p)	
			continue;
		int w[2];
		dfs(v, u, w);
		ret[1] += w[0], ret[0] += max(w[0], w[1]);
	}
}
int main() {
	int testcase, n, p;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &A[1]);
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 2; i <= n; i++) {
			scanf("%d %d", &p, &A[i]);
			g[i].push_back(p), g[p].push_back(i);
		}
		int w[2];
		dfs(1, -1, w);
		printf("%d\n", max(w[0], w[1]));
	}
	return 0;
}

