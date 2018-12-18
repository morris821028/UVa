#include <bits/stdc++.h> 
using namespace std;

// same HDU 5052 Yaoge's maximum profit 

const int64_t INF = 1LL<<60;
const int MAXN = 50005;
int K;
class LCT { // Link-Cut Tree
public:
    static const int MAXN = 65536;
    struct Node {
        static Node *EMPTY;
        Node *ch[2], *fa;
        int rev;
        int dp[61];
        int t, s;
        Node() {
            ch[0] = ch[1] = fa = NULL;
            rev = 0;
            memset(dp, 0, sizeof(dp[0])*K), t = s = 0;
        }
        bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }
        void update_rev() {
        	if (rev) {
                ch[0]->rev ^= 1, ch[1]->rev ^= 1;
                swap(ch[0], ch[1]);
                rev ^= 1;
            }
		}
        void pushdown() {
            update_rev();
        }
        void pushup() {
            if (this == EMPTY)	return ;
            if (ch[0] == EMPTY && ch[1] != EMPTY) {
            	memcpy(dp, ch[1]->dp, sizeof(dp[0])*(K));
			} else if (ch[1] == EMPTY && ch[0] != EMPTY) {
				memcpy(dp, ch[0]->dp, sizeof(dp[0])*(K));
			} else if (ch[0] != EMPTY && ch[1] != EMPTY) {
	            int i = 0;
	            for (; i + 8 <= K; i += 8) {
	            	dp[i] = max(ch[0]->dp[i], ch[1]->dp[i]);
	            	dp[i+1] = max(ch[0]->dp[i+1], ch[1]->dp[i+1]);
	            	dp[i+2] = max(ch[0]->dp[i+2], ch[1]->dp[i+2]);
	            	dp[i+3] = max(ch[0]->dp[i+3], ch[1]->dp[i+3]);
	            	dp[i+4] = max(ch[0]->dp[i+4], ch[1]->dp[i+4]);
	            	dp[i+5] = max(ch[0]->dp[i+5], ch[1]->dp[i+5]);
	            	dp[i+6] = max(ch[0]->dp[i+6], ch[1]->dp[i+6]);
	            	dp[i+7] = max(ch[0]->dp[i+7], ch[1]->dp[i+7]);
				}
				for (; i < K; i++)
					dp[i] = max(ch[0]->dp[i], ch[1]->dp[i]);
			} else {
				memset(dp, 0, sizeof(dp[0])*K);
			}
            dp[t-1] = max(dp[t-1], s);
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
    Node* newNode(int t = 0, int s = 0) {
        Node *u = &_mem[bufIdx++];
        *u = Node();
        u->fa = u->ch[0] = u->ch[1] = Node::EMPTY;
        u->t = t, u->s = s;
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
	void max_profit(Node *x, Node *y) {
		mk_root(x);
		access(y), splay(y);
		int g = 0, h = 0;
		static int ret[62];
		memset(ret, 0, sizeof(ret[0])*(K+1));
		for (int i = 1, mx_v = 0; i <= K; i++) {
			int v = y->dp[i-1];
			if (v == 0 || v <= mx_v)
				continue;
			mx_v = v;
			for (int j = i; j <= K; j++)
				ret[j] = max(ret[j], ret[j-i]+v);
		}
		for (int i = 0; i <= K; i++)
			g += ret[i], h ^= ret[i];
		printf("%d %d\n", g, h);
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
	static int t[50005], s[50005];
	int n, m, x, y, v;
	while (scanf("%d %d", &n, &K) == 2) {
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}
		for (int i = 1; i <= n; i++)
			scanf("%d", &t[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &s[i]);

		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode(t[i], s[i]);

		bfs(n);

		scanf("%d", &m);

		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			if (x > y)	swap(x, y);
			tree.max_profit(A[x], A[y]);
		}
	}
    return 0;
}
/*
5  10
1  2
2  3
2  4
1  5
1  2  3  4  5
10  15  30  45  50
2
1  1
5  4
*/
