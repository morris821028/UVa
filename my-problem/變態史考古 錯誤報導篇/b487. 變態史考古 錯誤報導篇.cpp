#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 100005;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int size;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0; 
			size = 1;
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
			size = 1;
			if (ch[0] != EMPTY)
				size += ch[0]->size;
			if (ch[1] != EMPTY)
				size += ch[1]->size;
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
	int path(Node *x, Node *y) {
		int ret;
		Node *u, *v = Node::EMPTY;
		access(y), splay(y);
		for (u = x; u != Node::EMPTY; u = u->fa) {
			splay(u), u->pushdown();
			if (u->fa == Node::EMPTY) {
				ret = u->ch[1]->size + v->size;
			}
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
		return ret;
	}
	inline int label(Node *x) {
		return x - _mem;
	}
} tree;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[100005], *node_x, *node_rt;

int main() {
	int n, m, x, y, c, u, v;
	char cmd[8];
	while (scanf("%d %d", &n, &m) == 2) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
		
		for (int i = 0; i < m; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'n') {		// link
				scanf("%d %d", &x, &y);
				tree.cut(A[x]);
				tree.link(A[x], A[y]);
			} else if (cmd[0] == 's') {	// sim
				scanf("%d %d", &x, &y);
				node_x = tree.lca(A[x], A[y]);
				int lca = tree.label(node_x);
				if (lca == 0) { 
					puts("-1");
				} else {
					node_rt = tree.find(A[lca]);
					int p1, p2, p3;
					p1 = tree.path(A[x], node_rt) + 1;
					p2 = tree.path(A[y], node_rt) + 1;
					p3 = tree.path(A[lca], node_rt) + 1;
					int a = p3 * 2, b = p1 + p2, g;
					g = __gcd(a, b), a /= g, b /= g;
					printf("%d/%d\n", a, b);
				} 
			}
		}
	}
	return 0;
}
/*
5 11
news 4 3
news 3 2
sim 3 4
sim 3 5
news 2 1
news 5 3
sim 3 4
sim 4 5
news 4 2
sim 4 5
sim 4 4
*/
