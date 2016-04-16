#include <bits/stdc++.h>
using namespace std;

int g[1024][1024];
vector<int> gg[1024];
int cc[1024];
int dfs(int u, int dep) {
	int ret = dep;
	for (auto v : gg[u]) {
		if (cc[v])	continue;
		int tmp = dfs(v, dep+1);
		ret = max(ret, tmp);
	}
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, A[1024];
		
		memset(g, 0, sizeof(g));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			gg[i].clear();
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]), g[i][A[i]] = 1, gg[A[i]].push_back(i);
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			int used[1024] = {};
			int u = i, cnt = 0;
			for (; used[u] == 0; u = A[u]) {
				used[u] = 1, cnt++;
			}
			if (u == i) 
				ret = max(ret, cnt);
		}
		memset(cc, 0, sizeof(cc));
		int cctot = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j)	continue;
				if (cc[i] || cc[j])	continue;
				if (g[i][j] == 0 || g[j][i] == 0)
					continue;
				cc[i] = 1, cc[j] = 1;
				cctot += 2;
				cctot += dfs(i, 0) + dfs(j, 0);
			}
		}
		ret = max(ret, cctot);
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}

