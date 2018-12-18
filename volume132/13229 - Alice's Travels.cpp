#include <bits/stdc++.h> 
using namespace std;

// same HDU 5052 Yaoge's maximum profit 

const int64_t INF = 1LL<<60;
const int MAXN = 50005;
class LCT { // Link-Cut Tree
public:
    static const int MAXN = 65536;
    struct Node {
        static Node *EMPTY;
        Node *ch[2], *fa;
        int rev;
        int64_t val, add, mx, mn, l, r;
        Node() {
            ch[0] = ch[1] = fa = NULL;
            rev = 0;
            val = 0, add = 0, mx = -INF, mn = INF;
            l = 0, r = 0;
        }
        bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }
        void update_rev() {
        	if (rev) {
                ch[0]->rev ^= 1, ch[1]->rev ^= 1;
                swap(l, r);
                swap(ch[0], ch[1]);
                rev ^= 1;
            }
		}
        void pushdown() {
            update_rev();
            if (add != 0) {
                if (ch[0] != EMPTY)	ch[0]->push_add(add);
                if (ch[1] != EMPTY)	ch[1]->push_add(add);
                add = 0;
            }
        }
        void pushup() {
            if (this == EMPTY)	return ;
            mx = mn = val;
            ch[0]->update_rev();
            ch[1]->update_rev();
            if (ch[0] != EMPTY)
                mx = max(ch[0]->mx, mx), mn = min(ch[0]->mn, mn);
            if (ch[1] != EMPTY)
                mx = max(ch[1]->mx, mx), mn = min(ch[1]->mn, mn);
            l = max(ch[0]->l, ch[1]->l);
            l = max(l, max(ch[1]->mx, val)-min(ch[0]->mn, val));
            r = max(ch[0]->r, ch[1]->r);
            r = max(r, max(ch[0]->mx, val)-min(ch[1]->mn, val));
        }
        inline void push_add(int64_t c) {
            if (this == EMPTY)	return ;
            add += c, val += c, mx += c, mn += c;
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
    Node* newNode(int w = 0) {
        Node *u = &_mem[bufIdx++];
        *u = Node();
        u->fa = u->ch[0] = u->ch[1] = Node::EMPTY;
        if (w)
        	u->val = w, u->mx = u->mn = w;
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
    void addPath(Node *x, Node *y, int w) {
    	mk_root(x);
    	access(y), splay(y);
    	y->push_add(w);
	}
	int64_t max_profit(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		return y->l;
	}
} tree;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[MAXN], *node_x, *node_y;
vector<int> g[MAXN];
void bfs(int n) {
	queue<int> Q;
	int visited[MAXN] = {};
	Q.push(1); visited[1] = 1;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (auto v : g[u]) {
			if (visited[v])
				continue;
			visited[v] = 1;
			A[v]->fa = A[u];
			Q.push(v);
		}
	}
}
int main() {
	static int w[50005];
	int n, m, x, y, v;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &w[i]), g[i].clear();

		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode(w[i]);

		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}

		bfs(n);

		scanf("%d", &m);
		
		int64_t sum = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &v);
			int64_t ret = tree.max_profit(A[x], A[y]);
			printf("%lld\n", ret);
			tree.addPath(A[x], A[y], v);
		}
	}
    return 0;
}
/*
3
1  2  3
1  2
2  3
2
1  2  100
1  3  100


5
1 2 3 4 5
1 2
2 3
3 4
4 5
5
1 5 1
5 1 1
1 1 2
5 1 1
1 2 1
*/
