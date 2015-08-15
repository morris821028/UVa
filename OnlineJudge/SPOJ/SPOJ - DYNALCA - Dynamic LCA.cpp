#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 131072;
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
//		if (x == y || find(x) != find(y))
//			return x;
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
} tree;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[131072], *node_x, *node_y;
int p[131072];
int main() {
	int n, m, x, y, c, u, v;
	char cmd[8];
	while (scanf("%d %d", &n, &m) == 2) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
				
		for (int i = 0; i < m; i++) {
			scanf("%s", cmd);
			if (cmd[1] == 'c') {		// lca
				scanf("%d %d", &x, &y);
				node_x = tree.lca(A[x], A[y]);
				printf("%d\n", tree.label(node_x));
			} else if (cmd[1] == 'i') {	// link
				scanf("%d %d", &x, &y);
				tree.link(A[x], A[y]);
			} else if (cmd[1] == 'u') {	// cut
				scanf("%d", &x);
				tree.cut(A[x]);
			}
		}
	}
	return 0;
}
/*
5 9
lca 1 1
link 1 2
link 3 2
link 4 3
lca 1 4
lca 3 4
cut 4
link 5 3
lca 1 5
*/
