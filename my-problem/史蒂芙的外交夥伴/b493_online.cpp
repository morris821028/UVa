#include <bits/stdc++.h> 
using namespace std;

class SegementTree {
public:
	static const int MAXN = 1000000;
	static const int MAXV = 100005;
	struct Node {
		Node *lson, *rson;
		int sum;
	    Node() {
	    	lson = rson = NULL;
	    	sum = 0;
	    }
	};
	int L, R, V, mem_idx;
	stack<Node*> mem_stk[MAXV];
	inline void clear_stk(int x) {
		while (!mem_stk[x].empty()) {
			delete mem_stk[x].top();
			mem_stk[x].pop();
		}
	}
	Node* init(int l, int r, int v) {
		L = l, R = r, V = v;
		for (int i = 0; i <= v; i++)
			clear_stk(i);
		Node* root = build(l, r);
		return root;
	}
	Node* newNode() {
		Node *u = new Node();
		*u = Node();
		mem_stk[mem_idx].push(u);
		return u;
	}
	Node* cloneNode(Node *p) {
		Node* u = new Node();
		*u = *p;
		mem_stk[mem_idx].push(u);
		return u;
	}
	Node* build(int l, int r) {
	    if (l > r)  return NULL;
	    Node *u = newNode();
	    if (l == r) {
		} else {
			int m = (l + r)/2;
	    	u->lson = build(l, m);
	    	u->rson = build(m+1, r);
		}
	    return u;
	}
	Node* change(Node *p, int x, int l, int r) {
		assert(p != NULL);
		Node *u = cloneNode(p);
		u->sum++;
	    if (l == r) {
	    } else {
	    	int mid = (l + r)/2;
	    	if (x <= mid)
	        	u->lson = change(p->lson, x, l, mid);
	    	else
	     		u->rson = change(p->rson, x, mid+1, r);
	    }
	    return u;
	}
	Node* change(Node *p, int x) {
		return change(p, x, L, R);
	}
	
	int QD;
	void find(Node *v1, Node *v2, Node *v3, int x, int l, int r) {
		if (1 <= l && r <= x) {
	    	QD += v1->sum + v2->sum - v3->sum * 2;
	    	return ;
	    }
	    int mid = (l + r)/2;
	    if (x <= mid) {
	        find(v1->lson, v2->lson, v3->lson, x, l, mid);
	    } else {
			find(v1->lson, v2->lson, v3->lson, x, l, mid);
			find(v1->rson, v2->rson, v3->rson, x, mid+1, r);
		}
	}
	void find(Node *v1, Node *v2, Node *v3, int x) {
		QD = 0;
	    find(v1, v2, v3, x, L, R);
	}
} tree;
const int MAXN = 65536;
const int MAXLOGN = 17;
SegementTree::Node *root[MAXN];

int A[MAXN];
int fa[MAXLOGN][MAXN], dep[MAXN];
int parent[MAXN], weight[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p, vector<int> &vA) {
	root[u] = tree.change(root[p], A[u]);
	fa[0][u] = p, dep[u] = dep[p] + 1;
	vA.push_back(u);
	for (auto v : g[u]) {
		if (v == p)	continue;
		dfs(v, u, vA);
	}
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int LCA(int x, int y) {
	if (dep[x] < dep[y])	swap(x, y);
	int d = dep[x] - dep[y];
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if ((d>>i)&1) {
			d -= 1<<i;
			x = fa[i][x];
		}
	}
	if (x == y)	return x;
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if (fa[i][x] != fa[i][y]) {
			x = fa[i][x], y = fa[i][y];
		}
	}
	return fa[0][x];
}
void merge(int X, int Y) {
	if (findp(X) == findp(Y))	return ;
	int rx, ry;
	rx = findp(X), ry = findp(Y);
	if (weight[rx] < weight[ry])	swap(rx, ry), swap(X, Y);
	g[X].push_back(Y), g[Y].push_back(X);
	// merge Y's group into X's group
	tree.clear_stk(ry), tree.mem_idx = rx;
	vector<int> vA;
	dfs(Y, X, vA);
	for (int i = 1; i < MAXLOGN; i++) {
		for (auto j : vA)
			fa[i][j] = fa[i-1][fa[i-1][j]];
	}	
	parent[ry] = rx, weight[rx] += weight[ry];
}
int path(int X, int Y, int K) {
	if (findp(X) != findp(Y))	return 0;
	int rx, ry, lca;
	rx = findp(X), ry = findp(Y);
	lca = LCA(X, Y);
	tree.find(root[X], root[Y], root[lca], K);
	tree.QD += A[lca] <= K;
	return tree.QD;
}
int main() {
	int N, Q, cmd;
	int X, Y, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
			
		for (int i = 1; i <= N; i++)
			parent[i] = i, weight[i] = 1, g[i].clear(), dep[i] = 0;
		for (int i = 0; i < MAXLOGN; i++)
			for (int j = 0; j <= N; j++)
				fa[i][j] = 0;
			
		tree.mem_idx = 0;
		root[0] = tree.init(1, N, N);
		for (int i = 1; i <= N; i++)
			root[i] = root[0];
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &cmd, &X, &Y);
			if (cmd == 0) {
				merge(X, Y);
			} else {
				scanf("%d", &K);
				printf("%d\n", path(X, Y, K));
			}
		}
		
		for (int i = 0; i <= N; i++)
			tree.clear_stk(i);
	}
	return 0;
}
/*
7 11
1 5 2 6 3 7 4
0 2 4
0 1 2
0 1 3
0 3 7
1 4 7 3
1 5 6 7
0 2 5
0 5 3
1 4 5 5
0 3 6
1 5 6 4
*/
