#include <bits/stdc++.h> 
using namespace std;
class LCT { // Link-Cut Tree
public:
	static const int MAXN = 50005;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
		}
		bool is_root() {
			return fa->ch[0] != this && fa->ch[1] != this;
		}
		void pushdown() {
			if (rev) {
				ch[0]->rev ^= 1, ch[1]->rev ^= 1;
				swap(ch[0], ch[1]);
				rev ^= 1;
			}
		}
		void pushup() {
			if (this == EMPTY)	return ;
		}
	} _mem[MAXN];
	
	int bufIdx;
	LCT() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
		bufIdx = 1; 
	}
	void init(int n = 0) {
		bufIdx = 1;
		for (int i = 1; i <= n; i++)
			newNode();
	}
	Node* newNode() {
		Node *u = &_mem[bufIdx++];
		*u = Node();
		u->fa = u->ch[0] = u->ch[1] = Node::EMPTY;
		return u;
	}
	void rotate(Node *x) {
		Node *y;
		int d;
		y = x->fa, d = y->ch[1] == x ? 1 : 0;
		x->ch[d^1]->fa = y, y->ch[d] = x->ch[d^1];
		x->ch[d^1] = y;
		if (!y->is_root())
			y->fa->ch[y->fa->ch[1] == y] = x;
		x->fa = y->fa, y->fa = x;
		y->pushup(), x->pushup();
	}
	void deal(Node *x) {
		if (!x->is_root())	deal(x->fa);
		x->pushdown();
	}
	void splay(Node *x) {
		Node *y, *z;
		deal(x);
		while (!x->is_root()) {
			y = x->fa, z = y->fa;
			if (!y->is_root()) {
				if (y->ch[0] == x ^ z->ch[0] == y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
		x->pushup();
	}
	Node* access(Node *u) {
		Node *v = Node::EMPTY;
		for (; u != Node::EMPTY; u = u->fa) {
			splay(u);
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
		return v;
	}
	void mk_root(Node *u) {
		access(u)->rev ^= 1, splay(u);
	}
	void cut(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		y->ch[0] = x->fa = Node::EMPTY;
	}
	Node* cut(Node *x) {
		Node *u, *v, *rt = find(x);
		mk_root(rt);
		access(x), splay(x);
		for (v = x->ch[0]; v->ch[1] != Node::EMPTY; v = v->ch[1]);
		x->ch[0]->fa = x->fa;
		x->fa = x->ch[0] = Node::EMPTY;
		return v;
	}
	void link(Node *x, Node *y) {
		mk_root(x);
		x->fa = y;
	}
	Node* find(Node *x) {
		for (x = access(x); x->pushdown(), x->ch[0] != Node::EMPTY; x = x->ch[0]);
		return x;
	}
	//
	Node* lca(Node *x, Node *y) {
		if (x == y)	return x;
		if (find(x) != find(y))
			return Node::EMPTY;
		Node *u, *v = Node::EMPTY, *LCA = Node::EMPTY;
		access(y), splay(y);
		for (u = x; u != Node::EMPTY; u = u->fa) {
			splay(u);
			if (u->fa == Node::EMPTY) {
				LCA = u;
//				u->ch[1]->push_add(c), v->push_add(c);
			}
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
		return LCA;
	}
	inline int label(Node *x) {
		return x - _mem;
	}
	inline Node* c(int x) {
		return _mem + x;
	}
} lct;
LCT::Node *LCT::Node::EMPTY;
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
	int L, R, V, mem_buf, mem_idx;
	queue<Node*> mem_bin[MAXV], bin;
	inline void clear_bin(int x) {
		while (!mem_bin[x].empty()) {
			recycle(mem_bin[x].front());
			mem_bin[x].pop();
		}
	}
	inline void recycle(Node *x) {
		bin.push(x);
	}
	Node* init(int l, int r, int v) {
		L = l, R = r, V = v;
		mem_buf = 0;
		for (int i = 0; i <= v; i++) {
			while (!mem_bin[i].empty())	mem_bin[i].pop();
		}
		while (!bin.empty())	bin.pop();
		Node* root = build(l, r);
		return root;
	}
	Node* newNode() {
		Node *u;
		if (mem_buf < MAXN) {
			u = &_mem[mem_buf++];
		} else {
			assert(!bin.empty());
			u = bin.front(), bin.pop();
		}
		*u = Node();
		mem_bin[mem_idx].push(u);
		return u;
	}
	Node* cloneNode(Node *p) {
		Node* u = newNode();
		*u = *p;
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
SegementTree::Node *root[MAXN];

int A[MAXN], dep[MAXN], fa[MAXN];
int parent[MAXN], weight[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p, vector<int> &vA) {
	dep[u] = dep[p]+1, fa[u] = p;
	vA.push_back(u);
	for (auto v : g[u]) {
		if (v == p)	continue;
		dfs(v, u, vA);
	}
}
void merge(int X, int Y) {
	if (lct.find(lct.c(X)) == lct.find(lct.c(Y)))	return ;
	int rx, ry;
	rx = lct.label(lct.find(lct.c(X)));
	ry = lct.label(lct.find(lct.c(Y)));
	if (weight[rx] < weight[ry])	swap(rx, ry), swap(X, Y);
	g[X].push_back(Y), g[Y].push_back(X);
	// merge Y's group into X's group
	tree.clear_bin(ry), tree.mem_idx = rx;
	vector<int> vA;
	dfs(Y, X, vA);
	for (auto u : vA)
		root[u] = tree.change(root[fa[u]], A[u]);
	lct.link(lct.c(Y), lct.c(X));
	weight[rx] += weight[ry];
}
int path(int X, int Y, int K) {
	int lca = lct.label(lct.lca(lct.c(X), lct.c(Y)));
	if (lca == 0)	
		return 0;
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
			parent[i] = i, weight[i] = 1, g[i].clear(), dep[i] = 0, fa[i] = i;
			
		tree.mem_idx = 0, lct.init(N);
		root[0] = tree.init(1, N, N);
		for (int i = 1; i <= N; i++)
			root[i] = root[0];
		
		int d = 0;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &cmd, &X, &Y);
			X ^= d, Y ^= d;
			if (cmd == 0) {
				merge(X, Y);
			} else {
				scanf("%d", &K), K ^= d;
				d = path(X, Y, K);
				printf("%d\n", d);
			}
		}
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

