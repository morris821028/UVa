#include <stdio.h> 
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
// http://oi.nks.edu.cn/showproblem?problem_id=2646 
#define MAXN 65536
#define LOGMAXN 17
vector<int> g[MAXN], invg[MAXN], tree[MAXN];
int indeg[MAXN] = {};
vector<int> toposort(vector<int> g[], int n) {
	vector<int> ret;
	queue<int> Q;
	int u, v;
	for (int i = 0; i <= n; i++)
		indeg[i] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < g[i].size(); j++)
			indeg[g[i][j]]++;
	}
	for (int i = 1; i <= n; i++) {
		if (indeg[i] == 0)
			Q.push(i);
	}
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		ret.push_back(u);
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if (--indeg[v] == 0)
				Q.push(v);
		}
	}
	return ret;
}

int depth[MAXN], parent[MAXN][LOGMAXN];
int getLCA(int x, int y) {
	int dist, i;
	if (depth[x] < depth[y])	swap(x, y);
	dist = depth[x] - depth[y];
	for (int i = 0; dist; i++, dist /= 2) {
		if (dist&1)	x = parent[x][i];
	}
	for (i = 0; x != y;) {
		if (parent[x][i] != parent[y][i] || (i == 0 && parent[x][i] == parent[y][i])) {
			x = parent[x][i];
			y = parent[y][i];
			i++;
		} else {
			i--;
		}
	}
	return x;
}
void buildTree(vector<int> &topo, vector<int> g[], int n) {
	for (int i = 1; i <= n; i++)
		tree[i].clear();
	int u, v;
	parent[0][0] = -1, depth[0] = 0;
	for (int i = 0; i < topo.size(); i++) {
		u = topo[i];
		if (g[u].size() == 0) {
			depth[u] = 1, parent[u][0] = 0;
			continue;
		}
		int lca = g[u][0];
		for (int j = 0; j < g[u].size(); j++)
			v = g[u][j], lca = getLCA(lca, v);
		depth[u] = depth[lca] + 1;
		parent[u][0] = lca;
		tree[lca].push_back(u);
		for (int i = 0; parent[u][i]; i++) {
			parent[u][i+1] = parent[parent[u][i]][i];
		}
	}
}

int used[MAXN], subtree[MAXN];
void sumTree(int n) {
	queue<int> Q;
	int u, v;
	for (int i = 1; i <= n; i++) {
		subtree[i] = 1;
		indeg[i] = tree[i].size();
		if (tree[i].size() == 0)	Q.push(i);
	}
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		v = parent[u][0];
		indeg[v]--;
		subtree[v] += subtree[u];
		if (indeg[v] == 0)
			Q.push(v);
	}
}
int main() {	
	int n, x, y, u, v;
	while(scanf("%d", &n) == 1) {
		for (int i = 0; i <= n; i++)
			g[i].clear(), invg[i].clear();
		for (int i = 1; i <= n; i++) {
			while (scanf("%d", &x) == 1 && x) {
				g[i].push_back(x);
				invg[x].push_back(i);
			}
		}
		vector<int> topo = toposort(invg, n);
		buildTree(topo, g, n);
		sumTree(n);
		for (int i = 1; i <= n; i++)
			printf("%d\n", subtree[i] - 1);
	}
	return 0;
}
