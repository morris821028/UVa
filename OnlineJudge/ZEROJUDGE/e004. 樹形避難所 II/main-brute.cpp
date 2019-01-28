#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65536;
set<int> G[MAXN];
int W[MAXN];
int used[MAXN], cases = 0;

int sum_tree(int u) {
	queue<int> Q;
	int sum = 0;
	cases++, used[u] = cases;
	Q.push(u);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		sum += W[u];
		for (auto v : G[u]) {
			if (used[v] != cases) {
				used[v]	 = cases;
				Q.push(v);
			}
		}
	}
	return sum;
}

int parent[MAXN];

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		int cmd, u, v, w;
		for (int i = 1; i <= n; i++)
			scanf("%d", &W[i]), G[i].clear(), parent[i] = -1;

		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &u, &v);
				assert(parent[u] == -1);
				G[v].insert(u), parent[u] = v;
			} else if (cmd == 2) {
				scanf("%d", &u);
				G[parent[u]].erase(u);
				parent[u] = -1;
			} else if (cmd == 3) {
				scanf("%d %d", &u, &w);
				W[u] = w;
			} else if (cmd == 4) {
				scanf("%d", &u);
				int p = sum_tree(u);
				printf("%d\n", p);
			}
		}
	}
	return 0;
}
/*
6 9999
0 0 0 1 1 1
1 1 2
4 1
1 3 4
4 3
1 2 3
4 3
2 1 2

*/

