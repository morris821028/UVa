#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;
vector<int> g[MAXN];
int indeg[MAXN];
int dfs(int u) {
	int ret = 1;
	for (auto &v : g[u])
		ret = max(ret, dfs(v)+1);
	return ret;
}
int solve(int root, int N) {
	return dfs(root);
}
int main() {
	int testcase, cases = 0;
	int N, M, u, v;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i <= N; i++)
			g[i].clear(), indeg[i] = 0;
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &u, &v);
			g[u].push_back(v), indeg[v]++;
		}
		
		int ret = 1;
		for (int i = 1; i <= N; i++) {
			if (indeg[i] == 0)
				ret = max(solve(i, N), ret);
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

