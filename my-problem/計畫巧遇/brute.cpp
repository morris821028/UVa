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
	int i;
	for (i = u; i != -1 && on[i] == 0; i = parent[i]);
	printf("%d", i);
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
			scanf("%s %d", cmd, &x);
			if (cmd[0] == 'S')
				search(x);
			if (cmd[0] == 'M') {
				int val = (!on[x]) - on[x];
				on[x] += val;
			}
		}
		puts("");
	}
	return 0;
}
/*
31
0 1
0 2
0 3
1 4
1 5
2 6 
2 7
3 8
4 9
4 10
4 11
6 12
6 13
12 14
12 15
13 16
13 17
14 18
14 19
14 20
17 21
17 22
20 23
21 24
21 25
22 26
22 27
23 28
24 29
24 30
10
M 6
S 29
S 9
M 0
S 9
S 6
S 2
M 6
S 29
S 6
*/

