#include <stdio.h> 
#include <vector>
#include <set>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;

#define MAXN 131072
int color[MAXN];
int hNext[MAXN], iNode[MAXN], aPos[MAXN];
int used[MAXN], nodesize = 0;
struct Node {
	int p, pPos, dep;
	vector<int> A;
	vector<int> seg[10];
	void init() {
		A.clear();
		p = -1, dep = 0;
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
int getSTsize(int n) {
	int ret = 1;
	for (ret = 1; ret < n; ret <<= 1);
	return ret<<1;
}
int prepare(int u, int p) {
	int sz = 1, mx = -1, hedge = -1;
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
void buildST(Node &nd, int k, int l, int r) {
	if (l > r)	return ;
	if (l == r) {
		nd.seg[color[nd.A[l]]][k] = 1;
		return;
	}
	int mid = (l + r)/2;
	buildST(nd, k<<1, l, mid);
	buildST(nd, k<<1|1, mid+1, r);
	for (int i = 0; i < 10; i++)
		nd.seg[i][k] = nd.seg[i][k<<1] + nd.seg[i][k<<1|1];
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
		for (int i = 0; i < 10; i++)
			nd.seg[i].clear(), nd.seg[i].resize(getSTsize(nd.A.size()), 0);
		buildST(nd, 1, 0, nd.A.size() - 1);
		if (p != -1) {
			nd.p = iNode[p], nd.pPos = aPos[p];
			nd.dep = nodes[nd.p].dep + 1;
		}
	}
	int v;
	for (int i = 0; i < tree.g[u].size(); i++) {
		v = tree.g[u][i];
		if (v == p)	continue;
		build(v, u);
	}
}

int colorsum[10];
void queryST(Node &nd, int k, int l, int r, int x, int y) {
	if (x <= l && r <= y) {
		for (int i = 0; i < 10; i++)
			colorsum[i] += nd.seg[i][k];
		return ;
	}
	int mid = (l + r)/2;
	if (x <= mid)
		queryST(nd, k<<1, l, mid, x, y);
	if (mid < y)
		queryST(nd, k<<1|1, mid+1, r, x, y);
	
}
void search(int u, int v) {
	memset(colorsum, 0, sizeof(colorsum));
	int x = iNode[u], y = iNode[v];
	u = aPos[u], v = aPos[v];
	while (x != y) {
		if (nodes[x].dep < nodes[y].dep)
			swap(x, y), swap(u, v);
		assert(u <= nodes[x].A.size());
		queryST(nodes[x], 1, 0, nodes[x].A.size() - 1, 0, u);
		u = nodes[x].pPos, x = nodes[x].p;
	}
	if (u > v)	swap(u, v);
	queryST(nodes[x], 1, 0, nodes[x].A.size() - 1, u, v);
	int ret = 0;
//	for (int i = 0; i < 10; i++)
//		printf("%d ", colorsum[i]);
//	puts("");
	for (int i = 0; i < 10; i++)
		ret = max(ret, colorsum[i]);
	printf("%d\n", ret);
}
void modifyST(Node &nd, int k, int l, int r, int x, int v) {
	if (l == r) {
		for (int i = 0; i < 10; i++)
			nd.seg[i][k] = 0;
		nd.seg[v][k]++;
		return ;
	}
	int mid = (l + r)/2;
	if (x <= mid)
		modifyST(nd, k<<1, l, mid, x, v);
	else
		modifyST(nd, k<<1|1, mid+1, r, x, v);
	for (int i = 0; i < 10; i++)
		nd.seg[i][k] = nd.seg[i][k<<1] + nd.seg[i][k<<1|1];
}
void modify(int u, int color) {
	int x = iNode[u];
	modifyST(nodes[x], 1, 0, nodes[x].A.size() - 1, aPos[u], color);
}
int main() {
//	freopen("in.txt","r+t",stdin);
//    freopen("out2.txt","w+t",stdout);
	int testcase;
	int n, q, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &q);
		for (int i = 0; i < n; i++)
			scanf("%d", &color[i]), color[i]--;
		tree.init(n);
		
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			tree.addEdge(x, y);
		}
		
		prepare(tree.root = 0, -1);
		memset(used, 0, sizeof(used));
		nodesize = 0;
		build(tree.root = 0, -1);
		
//		for (int i = 0; i < n; i++)
//			printf("[%d] %d\n", i, hNext[i]);
		int cmd, u, v;
		for (int i = 0; i < q; i++) {
			scanf("%d %d %d", &cmd, &u, &v);
			if (cmd == 0) {
				u--, v--;
				modify(u, v);
			} else {
				u--, v--;
				search(u, v);
			}
		}
	}
	return 0;
}
/*
2

5 6
3 2 1 2 3
1 2
2 3
2 4
1 5
1 3 5
0 1 1
0 2 1
1 3 5
0 2 4
1 2 4
2 1
5 6
1 2
1 2 2

Output
2
3
1
1
*/
