#include <bits/stdc++.h> 
using namespace std;

int log2int(int x){
	return __builtin_clz((int)1)-__builtin_clz(x);
}
class SegementTree {
public:
	static const int MAXN = 1000000;
	static const int MAXV = 50005;
	struct Node {
		Node *lson, *rson;
		int sum;
	    Node() {
	    	lson = rson = NULL;
	    	sum = 0;
	    }
	} _mem[MAXN];
	int L, R, V, mem_idx;
	Node* init(int l, int r, int v) {
		L = l, R = r, V = v;
		mem_idx = 0;
		Node* root = build(l, r);
		return root;
	}
	inline Node* newNode() {
		Node *u = &_mem[mem_idx++];
		*u = Node();
		return u;
	}
//	inline Node* cloneNode(Node *p) {
//		Node *u = &_mem[mem_idx++];
//		*u = *p;
//		return u;
//	}
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
	Node* change(Node *p, Node **sp, int x, int l, int r) {
//		Node *u = cloneNode(p);
		Node *u = *sp;
		*u = *p;
		u->sum++;
	    if (l == r) {
	    } else {
	    	int mid = (l + r)/2;
	    	if (x <= mid)
	        	u->lson = change(p->lson, sp+1, x, l, mid);
	    	else
	     		u->rson = change(p->rson, sp+1, x, mid+1, r);
	    }
	    return u;
	}
	Node* change(Node *p, Node **sp, int x) {
		return change(p, sp, x, L, R);
	}
	
	int QD;
	void find(Node *v1, int x, int l, int r) {
		if (1 <= l && r <= x) {
	    	QD += v1->sum;
	    	return ;
	    }
	    int mid = (l + r)/2;
	    if (x <= mid) {
	        find(v1->lson, x, l, mid);
	    } else {
			find(v1->lson, x, l, mid);
			find(v1->rson, x, mid+1, r);
		}
	}
	int find(Node *v1, int x) {
		QD = 0;
	    find(v1, x, L, R);
	    return QD;
	}
} tree;
const int MAXN = 50005;
const int MAXLOGN = 17;
SegementTree::Node *root[MAXN], *pre_mem[MAXN][MAXLOGN];

int A[MAXN];
int fa[MAXN][MAXLOGN], dep[MAXN];
int parent[MAXN], weight[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p, vector<int> &vA) {
	root[u] = tree.change(root[p], pre_mem[u], A[u]);
	fa[u][0] = p, dep[u] = dep[p] + 1;
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
	int LOGN = log2int(dep[x]);
	for (int i = LOGN; i >= 0; i--) {
		if ((d>>i)&1)
			d -= 1<<i, x = fa[x][i];
	}
	if (x == y)	return x;
	for (int i = LOGN; i >= 0; i--) {
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	}
	return fa[x][0];
}
void merge(int X, int Y) {
	if (findp(X) == findp(Y))	return ;
	int rx, ry;
	rx = findp(X), ry = findp(Y);
	if (weight[rx] > weight[ry])	swap(rx, ry), swap(X, Y);
	g[X].push_back(Y), g[Y].push_back(X);
	// merge Y's group into X's group
	parent[rx] = ry, weight[ry] += weight[rx];
	vector<int> vA;
	dfs(X, Y, vA);
	int LOGN = log2int(weight[ry]);
	for (int i = 1; i <= LOGN; i++) {
		for (auto j : vA)
			fa[j][i] = fa[fa[j][i-1]][i-1];
	}	
}
int path(int X, int Y, int K) {
	if (findp(X) != findp(Y))	return 0;
	int lca = LCA(X, Y);
	int ret = tree.find(root[X], K) + tree.find(root[Y], K) - tree.find(root[lca], K) * 2;
	ret += A[lca] <= K;
	return ret;
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
				fa[j][i] = 0;
			
		root[0] = tree.init(1, N, N);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < MAXLOGN; j++)
				pre_mem[i][j] = tree.newNode();
			root[i] = tree.change(root[0], pre_mem[i], A[i]);
		}
		
		int d = 0;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &cmd, &X, &Y);
			X ^= d, Y ^= d;
			if (cmd == 0) {
				merge(X, Y);
			} else {
				scanf("%d", &K);
				K ^= d;
				d = path(X, Y, K);
				printf("%d\n", d);
			}
		}
	}
	return 0;
}
