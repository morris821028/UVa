#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
    static const int MAXN = 262144;
    struct Node {
        static Node *EMPTY;
        Node *ch[2], *fa;
        int rev;
        int val, size;
        int gcd;
        Node() {
            ch[0] = ch[1] = fa = NULL;
            rev = 0;
            val = 0;
            gcd = 1, size = 1;
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
            gcd = this->val, size = 1;
            if (ch[0] != EMPTY) {
            	gcd = __gcd(gcd, ch[0]->gcd);
                size += ch[0]->size;
            }
            if (ch[1] != EMPTY) { 
                gcd = __gcd(gcd, ch[1]->gcd);
                size += ch[1]->size;
            } 
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
    int gcdPath(Node *x, Node *y) {
        mk_root(x);
        access(y), splay(y);
        return y->gcd;
    }
    // 
    void changeNode(Node *x, int c) {
    	mk_root(x);
    	x->val = c;
	}
    void debug(int n) {
    }
} tree;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[262144];

int W[131072];
int main() {
	int n, m, cmd, x, y;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &W[i]);
		tree.init();
		for (int i = 0; i < n; i++) {
			A[i] = tree.newNode();
			A[i]->val = W[i];
		}
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			tree.link(A[x], A[y]);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &cmd, &x, &y);
			if (cmd == 1) {
				printf("%d\n", tree.gcdPath(A[x], A[y]));
			} else {
				tree.changeNode(A[x], y);
			}
		}
	}
	return 0;
}
/*
5
5 15 20 15 9
0 2
0 3
3 1
3 4
9999
1 2 1
1 1 3
2 3 3
1 1 4
1 1 3
*/
