#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 65536;
	static const int MOD = 51061;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int val, sum, add, mul, size;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			val = sum = add = mul = size = 1;
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
			if (mul != 1) {
				if (ch[0] != EMPTY) ch[0]->push_mul(mul);
				if (ch[1] != EMPTY)	ch[1]->push_mul(mul);
				mul = 1;
			}
			if (add != 0) {
				if (ch[0] != EMPTY)	ch[0]->push_add(add);
				if (ch[1] != EMPTY)	ch[1]->push_add(add);
				add = 0;
			}
		}
		void pushup() {
			sum = val, size = 1;
			if (ch[0] != EMPTY)
				sum += ch[0]->sum, size += ch[0]->size;
			if (ch[1] != EMPTY)
				sum += ch[1]->sum, size += ch[1]->size;
			sum %= MOD;
		}
		inline void push_mul(long long c) {
			mul = (mul * c) % MOD;
			sum = (sum * c) % MOD;
			add = (add * c) % MOD;
			val = (val * c) % MOD;
		}
		inline void push_add(long long c) {
			val = val + c;
			add = add + c;
			sum = (sum + c * size)%MOD;
		}
	} _mem[MAXN];
	
	int bufIdx;
	LCT() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
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
		access(u), splay(u);
		u->rev ^= 1;
	}
	void cut(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		y->ch[0] = x->fa = Node::EMPTY;
	}
	void link(Node *x, Node *y) {
		mk_root(x);
		x->fa = y;
	}
	Node* find(Node *x) {
		access(x), splay(x);
		for (; x->ch[0] != Node::EMPTY; x = x->ch[0]);
		return x;
	}
	//
	void addPath(Node *x, Node *y, int c) {
		mk_root(x);
		access(y), splay(y);
		y->push_add(c);
	}
	void mulPath(Node *x, Node *y, int c) {
		mk_root(x);
		access(y), splay(y);
		y->push_mul(c);
	}
	int sumPath(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		return y->sum;
	}
} tree;
LCT::Node *LCT::Node::EMPTY;

int main() {
	int n, m, x, y, c, u, v;
	char cmd[16];
	LCT::Node *A[65536], *node_x, *node_y;
	while (scanf("%d %d", &n, &m) == 2) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
		
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			tree.link(A[x], A[y]);
		}
		
		for (int i = 0; i < m; i++) {
			scanf("%s %d %d", cmd, &x, &y);
			if (cmd[0] == '+') {
				scanf("%d", &c);
				tree.addPath(A[x], A[y], c);
			} else if (cmd[0] == '-') {
				scanf("%d %d", &u, &v);
				tree.cut(A[x], A[y]);
				tree.link(A[u], A[v]);
			} else if (cmd[0] == '*') {
				scanf("%d", &c);
				tree.mulPath(A[x], A[y], c);
			} else if (cmd[0] == '/') {
				printf("%d\n", tree.sumPath(A[x], A[y]));
			}
		}
	}
	return 0;
}
/*
3 2
1 2
2 3
* 1 3 4
/ 1 1
*/
