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
	set< pair<int, int> > seg;
	void init() {
		A.clear(), seg.clear();
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
		nd.seg.clear();
		// build segment tree()
		if (p != -1)	nd.p = iNode[p], nd.pPos = aPos[p];
	}
	int v;
	for (int i = 0; i < tree.g[u].size(); i++) {
		v = tree.g[u][i];
		if (v == p)	continue;
		build(v, u);
	}
}
void search(int u) {
	int wh = -1;
	set< pair<int, int> >::iterator it, jt;
	for (int i = iNode[u], in = aPos[u]; i != -1; in = nodes[i].pPos, i = nodes[i].p) {
		if (nodes[i].seg.size() == 0)	continue;
		if (nodes[i].seg.begin()->first > in)	continue;
		it = upper_bound(nodes[i].seg.begin(), nodes[i].seg.end(), make_pair(in, 0x3f3f3f3f));
		if (it != nodes[i].seg.begin()) {
			jt = it, jt--;
			wh = jt->second;
			break;
		}
	}
	printf("%d\n", wh);
}
void modify(int u, int val) {
	Node &nd = nodes[iNode[u]];
	int pos = aPos[u];
	if (val == 1)
		nd.seg.insert(make_pair(aPos[u], u));
	else
		nd.seg.erase(make_pair(aPos[u], u));
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
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
			scanf("%s %d", cmd, &x);
			if (cmd[0] == 'S')
				search(x);
			if (cmd[0] == 'M') {
				int val = (!on[x]) - on[x];
				on[x] += val;
				modify(x, val);
			}
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
10
M 1
S 8
S 4
M 0
M 7
M 9
S 5
M 3
M 8
S 5

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
