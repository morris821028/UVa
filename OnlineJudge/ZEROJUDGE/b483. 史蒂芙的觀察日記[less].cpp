#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 262144;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int val;
		Node *mxv;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			val = 0;
			mxv = this;
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
			mxv = this;
			if (ch[0] != EMPTY) {
				if (ch[0]->mxv->val > mxv->val)	mxv = ch[0]->mxv;
			}
			if (ch[1] != EMPTY) { 
				if (ch[1]->mxv->val > mxv->val)	mxv = ch[1]->mxv;
			} 
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
	Node* maxPath(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		return y->mxv;
	}
	inline Node* c(int x) {
		return &_mem[x];
	}
} tree;
LCT::Node *LCT::Node::EMPTY;
int x[131072], y[131072];
int main() {
	int n, m, w, u, v, cmd;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		printf("Case #%d\n", ++cases);
		
		tree.init(n+m);
		
		int vcnt = n+1, mst = 0;
		for (int i = 1; i <= m; i++) {
			int tx, ty, vx, vy;
			scanf("%d %d %d", &tx, &ty, &w);
			x[i] = tx, y[i] = ty;
			tree.c(i+n)->val = w;
			if (tree.find(tree.c(tx)) != tree.find(tree.c(ty))) {
				tree.link(tree.c(tx), tree.c(i+n));
				tree.link(tree.c(ty), tree.c(i+n));
				mst += w;
			} else {
				LCT::Node *e = tree.maxPath(tree.c(tx), tree.c(ty));
				if (e->val > w) {
					mst += w - e->val;
					int eid = e - tree._mem - n;
					vx = x[eid], vy = y[eid];
					tree.cut(tree.c(vx), e);
					tree.cut(tree.c(vy), e);
					tree.link(tree.c(tx), tree.c(i+n));
					tree.link(tree.c(ty), tree.c(i+n));
				}
			}
			printf("%d\n", mst);
		}
	}
	return 0;
}
/*
3 3
1 2 1
1 3 2
2 3 4
*/

