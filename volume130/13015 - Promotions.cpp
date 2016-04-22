#include <bits/stdc++.h>
using namespace std;
// O(VE)
const int MAXN = 5005;
int A, B, E, P;
vector<int> G[MAXN], invG[MAXN];
int used[MAXN] = {}, cases = 0;
int dfs(int u, vector<int> g[]) {
	if (used[u] == cases)	return 0;
	used[u] = cases;
	int ret = 1;
	for (auto v : g[u])
		ret += dfs(v, g);
	return ret;
}
int main() {
	int x, y;
	while (scanf("%d %d %d %d", &A, &B, &E, &P) == 4) {
		for (int i = 0; i < E; i++)
			G[i].clear(), invG[i].clear();
		// Must DAG
		for (int i = 0; i < P; i++) {
			scanf("%d %d", &x, &y);
			G[x].push_back(y), invG[y].push_back(x);
		}
		
		int retA = 0, retB = 0, retN = 0;
		for (int i = 0; i < E; i++) {
			int worst, best;
			cases++;
			worst = E - dfs(i, G) + 1;
			cases++;
			best = dfs(i, invG);
			if (worst <= A)	retA++;
			if (worst <= B)	retB++;
			if (best > B)	retN++;
		}
		printf("%d\n%d\n%d\n", retA, retB, retN);
	}
	return 0;
}
