#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 65536;
	struct Node {
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
	} _mem[MAXN], *EMPTY;
	int bufIdx;
	LCT() {
		EMPTY = &_mem[0];
		EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
		bufIdx = 1; 
	}
	void init() {
		bufIdx = 1;
	}
	Node* newNode() {
		Node *u = &_mem[bufIdx++];
		*u = Node();
		u->fa = u->ch[0] = u->ch[1] = EMPTY;
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
	}
	Node* access(Node *u) {
		Node *v = EMPTY;
		for (; u != EMPTY; u = u->fa) {
			splay(u);
			u->ch[1] = v;
			v = u;
		}
		return v;
	}
	void mk_root(Node *u) {
		access(u), splay(u);
		u->rev ^= 1;
	}
	void cut(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		y->ch[0] = x->fa = EMPTY;
	}
	void link(Node *x, Node *y) {
		mk_root(x);
		x->fa = y;
	}
	Node* find(Node *x) {
		access(x), splay(x);
		for (; x->ch[0] != EMPTY; x = x->ch[0]);
		return x;
	}
} tree;

int main() {
	int n, m, x, y;
	char cmd[16];
	LCT::Node *A[65536], *node_x, *node_y;
	while (scanf("%d %d", &n, &m) == 2) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
		
		for (int i = 0; i < m; i++) {
			scanf("%s %d %d", cmd, &x, &y);
			if (cmd[0] == 'Q') {
				node_x = tree.find(A[x]);
				node_y = tree.find(A[y]);
				if (node_x == node_y) 
					puts("Yes");
				else
					puts("No");
			} else if (cmd[0] == 'C') {
				tree.link(A[x], A[y]);
			} else {
				tree.cut(A[x], A[y]);
			}
		}
	}
	return 0;
}
