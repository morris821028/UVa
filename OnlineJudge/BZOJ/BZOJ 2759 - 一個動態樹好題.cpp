#include <bits/stdc++.h> 
using namespace std;
const int MOD = 10007;
int INV[MOD];
class LCT { // Link-Cut Tree
public:
	static const int MAXN = 65536;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa, *sfa;
		int rev;
		int k, b, vk, vb;
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
		void pushup() {
			int tk = 1, tb = 0;
			if (ch[0] != EMPTY)
				tk = (tk*ch[0]->k)%MOD, tb = (tb*ch[0]->k + ch[0]->b)%MOD;
			tk = (tk*vk)%MOD, tb = (tb*vk + vb)%MOD;
			if (ch[1] != EMPTY)
				tk = (tk*ch[1]->k)%MOD, tb = (tb*ch[1]->k + ch[1]->b)%MOD;
			k = tk, b = tb;
		}
	} _mem[MAXN];
	
	int bufIdx;
	LCT() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
		Node::EMPTY->k = 1, Node::EMPTY->b = 0;
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
	inline void mov_root(Node *u) {
		access(u), splay(u);
	}
	int solve(Node *x) {
		Node *rt = find(x);
		mov_root(rt->sfa);
		int k = rt->sfa->k, b = rt->sfa->b;
		if (k == 1)	return b == 0 ? -2 : -1;
		int rt_x = (MOD-b)*INV[(k+MOD-1)%MOD]%MOD;
		mov_root(x);
		return (x->k * rt_x + x->b)%MOD;
	}
	void change(Node *x, int k, Node *p, int b) {
		// step 1. move old edge
		Node *rt = find(x);
		x->vk = k, x->vb = b, x->pushup();
		if (rt == x) {
			x->sfa = Node::EMPTY;
		} else {
			mov_root(x);
			x->ch[0]->fa = Node::EMPTY;
			x->ch[0] = Node::EMPTY;
			x->pushup();
			if (find(rt->sfa) != rt) {
				mov_root(rt);
				rt->fa = rt->sfa;
				rt->sfa = Node::EMPTY;
			}
		}
		// step 2. add new edge
		mov_root(x);
		if (find(p) == x)	x->sfa = p;
		else				x->fa = p;
	}
} tree;
const int MAXN = 65536;
LCT::Node *LCT::Node::EMPTY;
LCT::Node *A[MAXN];

int K[MAXN], P[MAXN], B[MAXN];
int visited[65536], visIdx;
void dfs(int u) {
	visited[u] = visIdx;
	if (visited[P[u]] == visIdx) { // cycle
		A[u]->sfa = A[u]->fa;
		A[u]->fa = LCT::Node::EMPTY;
		return ;
	}
	if (visited[P[u]] == 0)
		dfs(P[u]);
}
void exgcd(long long  x, long long y, long long &g, long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long inverse(long long x, long long p) {
	long long g, b, r;
	exgcd(x, p, g, r, b);
	if (g < 0)	r = -r;
	return (r%p + p)%p;
}
int main() {
	for (int i = 1; i < MOD; i++)
		INV[i] = inverse(i, MOD);
	int n, m, x, k, p, b;
	char cmd[16];
	while (scanf("%d", &n) == 1) {
		tree.init();
		for (int i = 1; i <= n; i++)
			A[i] = tree.newNode();
		
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &K[i], &P[i], &B[i]);
			A[i]->vk = K[i];
			A[i]->vb = B[i];
			A[i]->fa = A[P[i]];
		}
		
		memset(visited, 0, sizeof(visited)), visIdx = 0;
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0)
				visIdx++, dfs(i);
		}
		
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s %d", cmd, &x);
			if (cmd[0] == 'A') {
				printf("%d\n", tree.solve(A[x]));
			} else {
				scanf("%d %d %d", &k, &p, &b);
				tree.change(A[x], k, A[p], b);
			}
		}
	}
	return 0;
}
