#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 131072;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int val, lazy, sum, size;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			val = sum = 0, size = 1;
			lazy = 0;
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
			if (lazy != 0) {
				if (ch[0] != EMPTY)	ch[0]->push_add(lazy);
				if (ch[1] != EMPTY)	ch[1]->push_add(lazy);
				lazy = 0;
			}
		}
		void pushup() {
			if (this == EMPTY)	return ;
			sum = val, size = 1;
			if (ch[0] != EMPTY)
				sum |= ch[0]->sum, size += ch[0]->size;
			if (ch[1] != EMPTY)
				sum |= ch[1]->sum, size += ch[1]->size;
		}
		inline void push_add(int c) {
			if (this == EMPTY)	return ;
			val += c, sum += c;
			lazy += c;
		}
	} _mem[MAXN];
	
	int bufIdx;
	LCT() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
		Node::EMPTY->size = 0;
		bufIdx = 1; 
	}
	void init() {
		bufIdx = 1;
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
	void addPath(Node *x, Node *y, int c) {
//		Node *u, *v = Node::EMPTY;
//		access(y), splay(y);
//		for (u = x; u != Node::EMPTY; u = u->fa) {
//			splay(u);
//			if (u->fa == Node::EMPTY) {
//				u->ch[1]->push_add(c), v->push_add(c);
//			}
//			u->ch[1] = v;
//			v = u;
//			v->pushup();
//		}
		mk_root(x);
		access(y), splay(y);
		y->push_add(c);
	}
	int label(Node *u) {
		return u - _mem;
	}
} tree[2];
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[2][131072], *node_x, *node_y;
int fa[131072], color[131072];
vector<int> g[131072];
int dfs(int u, int p) {
	int sz = 1;
	for (auto v : g[u]) {
		if (v == p)	continue;
		sz += dfs(v, u);
	}
	fa[u] = p;
	A[0][u]->val = A[0][u]->sum = sz;
	A[1][u]->val = A[0][u]->sum = 1;
	if (p)	A[0][u]->fa = A[0][p];
	return sz;
}
int count_connect(int u) {
	int a = color[u], rt;
	tree[a].access(A[a][u]);
	rt = tree[a].label(tree[a].find(A[a][u]));
	tree[a].splay(A[a][rt]);
	if (color[rt] == color[u])
		return A[a][rt]->val;
	LCT::Node *v = A[a][rt]->ch[1];
	for (; v->pushdown(), v->ch[0] != LCT::Node::EMPTY; v = v->ch[0]);
	return v->val;
}
void change(int u) {
	int p = fa[u];
	int a = color[u], b = color[u]^1;
	if (p) {
		tree[a].access(A[a][u]);
		tree[a].addPath(tree[a].find(A[a][u]), A[a][p], -A[a][u]->val);
		tree[a].cut(A[a][u]);
		
		tree[b].access(A[b][u]);
		tree[b].link(A[b][u], A[b][p]);
		tree[b].addPath(tree[b].find(A[b][u]), A[b][p], A[b][u]->val);
	}
	color[u] ^= 1; 
}
int main() {
	int n, m, x, y, u, v, cmd;
	while (scanf("%d", &n) == 1) {
		tree[0].init();
		tree[1].init();
		for (int i = 1; i <= n; i++) {
			A[0][i] = tree[0].newNode();
			A[1][i] = tree[1].newNode();
			g[i].clear(), color[i] = 0;
		}
		
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		dfs(1, 0);
		
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &cmd, &u);
			if (cmd == 0) {
				printf("%d\n", count_connect(u));
			} else {
				change(u);
			}
		}
	}
	return 0;
}
/*
7
1 2
1 3
2 4
2 5
3 6
3 7
9999
0 1
1 1
0 2
0 3
1 1
0 2 
1 2
0 3
*/
