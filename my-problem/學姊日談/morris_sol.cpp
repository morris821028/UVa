#include <stdio.h> 
#include <vector>
#include <set>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 32767
int hNext[MAXN], iNode[MAXN], aPos[MAXN];
int used[MAXN], nodesize = 0;
struct Node {
	int p, pPos;
	vector<int> A;
	vector<int> BIT;
	void init() {
		A.clear(), BIT.clear();
		p = -1;
	}
} nodes[262144];
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
int prepare(int u, int p) {
	int sz = 1, mx = 0, hedge = -1;
	int v, t;
	for (int i = 0; i < tree.g[u].size(); i++) {
		v = tree.g[u][i], t;
		if (v == p)	continue;
		sz += (t = prepare(v, u));
		if (mx < t)
			mx = t, hedge = v;
	}
	hNext[u] = hedge;
	return sz;
}
void build(int u, int p) {	
	if (used[u] == 0) {
		Node &nd = nodes[++nodesize];
		nd.init();
		for (int i = u; i != -1; i = hNext[i]) {
			used[i] = 1;
			iNode[i] = nodesize, aPos[i] = nd.A.size();
			nd.A.push_back(i);
		}
		nd.BIT.clear(), nd.BIT.resize(nd.A.size() + 10, 0);
		if (p != -1)	nd.p = iNode[p], nd.pPos = aPos[p];
	}
	int v;
	for (int i = 0; i < tree.g[u].size(); i++) {
		v = tree.g[u][i];
		if (v == p)	continue;
		build(v, u);
	}
}
int queryBIT(vector<int> &BIT, int x) {
	int ret = 0;
	while (x)
		ret += BIT[x], x -= x&(-x);
	return ret;
}
void modifyBIT(vector<int> &BIT, int x, int val, int L) {
	while (x <= L)
		BIT[x] += val, x += x&(-x);
}
void search(int u) {
	int sum = 0;
	set< pair<int, int> >::iterator it, jt;
	for (int i = iNode[u], in = aPos[u]; i != -1; in = nodes[i].pPos, i = nodes[i].p)
		sum += queryBIT(nodes[i].BIT, in + 1);
	printf("%d", sum);
	puts("");
}
void modify(int u, int val) {
	Node &nd = nodes[iNode[u]];
	int pos = aPos[u];
	modifyBIT(nd.BIT, pos + 1, val, nd.A.size());
}
int main() {
	int n, q, x, y;
	char cmd[10];
	while (scanf("%d", &n) == 1) {
		tree.init(n);
		
		int on[MAXN] = {};
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			tree.addEdge(x, y);
		}
		
		prepare(tree.root = 0, -1);
		memset(used, 0, sizeof(used));
		nodesize = 0;
		build(tree.root = 0, -1);
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			modify(x, y);
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
