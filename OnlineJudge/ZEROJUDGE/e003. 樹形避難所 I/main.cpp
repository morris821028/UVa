#include <bits/stdc++.h>
using namespace std;
  
class LCT { // Link-Cut Tree
public:
    static const int MAXN = 30005;
    struct Node;
    static Node *EMPTY;
    static Node _mem[MAXN];
    static int bufIdx;
    struct Node {
        Node *ch[2], *fa;
        int rev;
        int vsize, size, val;
        void init() {
            ch[0] = ch[1] = fa = NULL;
            size = 0, vsize = 0, rev = 0;
        }
        bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }
        void pushdown() {
        	if (rev) {
        		ch[0]->rev ^= 1;
				ch[1]->rev ^= 1;
        		swap(ch[0], ch[1]);
        		rev = 0;
			}
        }
        void pushup() {
        	if (this == EMPTY)
        		return;
        	size = ch[0]->size + ch[1]->size + val + vsize;
		}
    };
    LCT() {
        EMPTY = &_mem[0];
        EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
        EMPTY->size = 0;
        bufIdx = 1; 
    }
    void init() {
        bufIdx = 1;
    }
    Node* newNode() {
        Node *u = &_mem[bufIdx++];
        u->init();
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
        y->pushup(), x->pushup();
    }
    void deal(Node *x) {
        if (!x->is_root())   deal(x->fa);
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
        x->pushdown();
    }
    Node* access(Node *u) {
        Node *v = EMPTY;
        for (; u != EMPTY; u = u->fa) {
            splay(u);
            u->vsize += u->ch[1] != EMPTY ? u->ch[1]->size : 0;
            u->vsize -= v != EMPTY ? v->size : 0;
            u->ch[1] = v;
            u->pushup();
            v = u;
        }
        return v;
    }
    void mk_root(Node *u) {
        access(u)->rev ^= 1, splay(u);
    }
    void cut(Node *x, Node *y) {
    	mk_root(x);
    	access(y), splay(y);
//    	debug(10);
    	assert(y->ch[0] == x);
        y->ch[0] = x->fa = EMPTY;
        y->pushup();
	}
    void link(Node *x, Node *y) {
    	mk_root(y);
    	access(x), splay(x);
        y->fa = x;
        x->vsize += y->size;
        x->pushup();
    }
    Node* find(Node *x) {
		access(x), splay(x);
		for (; x->ch[0] != EMPTY; x = x->ch[0]);
		return x;
	}
    void set(Node *x, int val) {
    	mk_root(x);
    	x->val = val;
    	x->pushup();
    }
    int get(Node *u) {
    	mk_root(u);
    	return u->size;
	}
	int same(Node *x, Node *y) {
		return find(x) == find(y);
	}
	void debug(int n) {
		return;
		puts("==================");
		for (int i = 1; i <= n; i++) {
			Node *u = &_mem[i];
			printf("[%d] %d, %d %d, %d %d %d\n", i, u->fa-_mem, u->ch[0]-_mem, u->ch[1]-_mem, u->size, u->vsize, u->val);
		}
	}
} lct;
LCT::Node *LCT::EMPTY, LCT::_mem[LCT::MAXN];
int LCT::bufIdx;
LCT::Node *node[LCT::MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		lct.init();
		int cmd, u, v, w;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &w);
			node[i] = lct.newNode();
			lct.set(node[i], w);
		}

		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &u, &v);
				lct.link(node[u], node[v]);
			} else if (cmd == 2) {
				scanf("%d %d", &u, &v);
				lct.cut(node[u], node[v]);
			} else if (cmd == 3) {
				scanf("%d %d", &u, &w);
				lct.set(node[u], w);
			} else if (cmd == 4) {
				scanf("%d", &u);
				int p = lct.get(node[u]);
				printf("%d\n", p);
			} else {
				scanf("%d %d", &u, &v);
				int f = lct.same(node[u], node[v]);
				printf("%d\n", f);
			}
			lct.debug(10);
		}
	}
	return 0;
}
/*
4 11
0 0 0 1 
1 1 2
4 1
1 3 4
4 3
1 2 3
4 1
2 1 2
4 2
4 1
3 3 2
4 2
*/

