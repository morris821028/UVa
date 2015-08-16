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
		inline void push_deal(int c) {
			if (this == EMPTY)	return ;
			val = c;
		}
		inline void push_add(int c) {
			if (this == EMPTY)	return ;
			val = sum = c;
			lazy = c;
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
	Node* _cut(Node *rt, Node *x) {
		Node *u, *v;
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
	void alter(Node *x, Node *y, int c) {
		if (x == y)		return ;
		Node *rt = find(x), *fx = Node::EMPTY;
		if (rt != x)
			fx = _cut(rt, x);
		if (x == find(y)) {	// resume
			if (fx != Node::EMPTY)
				link(x, fx);
		} else {
			link(x, y);
			x->push_deal(c);
		}
	}
	void paint(Node *x, Node *y, int c) {
		if (x == y || find(x) != find(y))
			return ;
		Node *u, *v = Node::EMPTY;
		access(y), splay(y);
		for (u = x; u != Node::EMPTY; u = u->fa) {
			splay(u);
			if (u->fa == Node::EMPTY) {
				u->ch[1]->push_add(c), v->push_add(c);
			}
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
	}
	pair<int, int> orPath(Node *x, Node *y) {
		if (x == y || find(x) != find(y))
			return {0, 0};
		pair<int, int> ret;
		Node *u, *v = Node::EMPTY;
		access(y), splay(y);
		for (u = x; u != Node::EMPTY; u = u->fa) {
			splay(u), u->pushdown();
			if (u->fa == Node::EMPTY) {
				ret = {u->ch[1]->size + v->size, u->ch[1]->sum | v->sum};
			}
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
		return ret;
	}
	void debug(int n) {
		for (int i = 1; i <= n; i++)
			printf("[%2d] l %2d r %2d fa %2d rev %2d, val %d lazy %d, %d\n", i, _mem[i].ch[0] - _mem, 
													_mem[i].ch[1] - _mem,
													_mem[i].fa - _mem, 
													_mem[i].rev,
													__builtin_ffs(_mem[i].val)-1,
													__builtin_ffs(_mem[i].lazy)-1,
													_mem[i].sum);
	}
} tree;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[131072], *node_x, *node_y;
int p[131072];
int main() {
	int n, m, x, y, c, u, v, cmd;
	while (scanf("%d %d", &n, &m) == 2) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
		
		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
			if (p[i])
				A[i]->fa = A[p[i]];
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &c);
			if (p[i])
				A[i]->push_deal(1<<c);
		}
		
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d %d", &x, &y, &c);
				tree.alter(A[x], A[y], 1<<c);
			} else if (cmd == 2) {
				scanf("%d %d %d", &x, &y, &c);
				tree.paint(A[x], A[y], 1<<c);
			} else if (cmd == 3) {
				scanf("%d %d", &x, &y);
				pair<int, int> r = tree.orPath(A[x], A[y]);
				printf("%d %d\n", r.first, __builtin_popcount(r.second));
			}
		}
	}
	return 0;
}
/*
6 6
0 1 1 3 3 0
1 2 1 1 1 1
3 2 3
1 3 2 30 
3 2 3
3 5 6
1 6 1 1
3 4 6

10 10
0 0 1 3 1 1 6 6 2 5
8 19 13 19 29 16 23 6 22 7
1 1 2 17
3 2 3
1 10 3 10
2 8 6 29
1 10 7 6
1 6 4 9
2 9 1 18
2 2 7 19
3 8 1
3 1 2
*/
