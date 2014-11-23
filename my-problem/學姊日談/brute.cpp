#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

#define MAXN 32767
struct Tree {
	vector<int> g[MAXN];
	int root;	
	void init(int n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		root = 0;
	}
	void addEdge(int x, int y) {
		g[x].push_back(y);
		g[y].push_back(x);
	}
} tree;

int on[MAXN] = {}, parent[MAXN] = {};
void dfs(int u, int p) {
	int v, t;
	for (int i = 0; i < tree.g[u].size(); i++) {
		v = tree.g[u][i], t;
		if (v == p)	continue;
		dfs(v, u);
	}
	parent[u] = p;
}
void search(int u) {
	int i, ret = 0;
	for (i = u; i != -1; i = parent[i])
		ret += on[i];
	printf("%d", ret);
	puts("");
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out1.txt", "w+t", stdout); 
	int n, q, x, y;
	char cmd[10];
	while (scanf("%d", &n) == 1) {
		tree.init(n);
		
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			tree.addEdge(x, y);
		}
		
		memset(on, 0, sizeof(on));
		dfs(0, -1);
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			on[x] += y;
			search(x);
		}
		puts("");
	}
	return 0;
}
/*
10
0 1
0 2
1 3
0 4
3 5
4 6
5 7
5 8
4 9
5
1 1
5 2
3 0
0 4
4 8
*/

