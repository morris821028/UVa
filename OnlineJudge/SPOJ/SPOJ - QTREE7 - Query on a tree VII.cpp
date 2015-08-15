#include <bits/stdc++.h> 
using namespace std;

class LCT { // Link-Cut Tree
public:
	static const int MAXN = 131072;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int val, mxv;
		multiset<int> s; // connected component (dashed)
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			val = mxv = 0;
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
			mxv = val;
			if (s.size())
				mxv = max(mxv, *s.rbegin());
			if (ch[0] != EMPTY)
				mxv = max(mxv, ch[0]->mxv);
			if (ch[1] != EMPTY)
				mxv = max(mxv, ch[1]->mxv);
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
			if (u->ch[1] != Node::EMPTY)
				u->s.insert(u->ch[1]->mxv);
			if (v != Node::EMPTY)
				u->s.erase(u->s.find(v->mxv));
			u->ch[1] = v;
			v = u;
			v->pushup();
		}
		return v;
	}
	void cut(Node *x) {
		access(x), splay(x);
		x->ch[0]->fa = x->fa;
		x->fa = x->ch[0] = Node::EMPTY;
		x->pushup();
	}
	void link(Node *x, Node *y) {
		access(y), splay(y);
		splay(x);
		x->fa = y;
		y->ch[1] = x;
		y->pushup();
	}
	Node* find(Node *x) {
		for (x = access(x); x->pushdown(), x->ch[0] != Node::EMPTY; x = x->ch[0]);
		return x;
	}
	//
	int label(Node *u) {
		return u - _mem;
	}
	inline Node* c(int x) {
		return &_mem[x];
	}
	int max_connect(Node *u) {
		Node *rt = find(u);
		splay(rt);
		return rt->ch[1]->mxv;
	}
	void change(Node *u, int val) {
		access(u), splay(u);
		u->val = val;
		u->pushup();
	}
} tree[2];
LCT::Node *LCT::Node::EMPTY;
int fa[131072], color[131072];
vector<int> g[131072];
void dfs(int u, int p) {
	fa[u] = p;
	int a = color[u];
	for (auto v : g[u]) {
		if (v == p)	continue;
		dfs(v, u);
		tree[color[v]].c(u)->s.insert(tree[color[v]].c(v)->mxv);
	}
	tree[a].c(u)->fa = tree[a].c(p);
	tree[a].c(u)->pushup();
	tree[a^1].c(u)->pushup(); 
}
int main() {
	int n, m, x, y, u, v, cmd;
	while (scanf("%d", &n) == 1) {
		tree[0].init(n+1);
		tree[1].init(n+1);
		for (int i = 1; i <= n+1; i++)
			g[i].clear(), color[i] = 0;
		
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for (int i = 1; i <= n; i++)
			scanf("%d", &color[i]);
		for (int i = 1, val; i <= n; i++) {
			scanf("%d", &val);
			tree[0].c(i)->val = val;
			tree[1].c(i)->val = val;
		}
		
		int vr = n+1;
		dfs(1, vr);
		tree[color[1]].c(vr)->s.insert(tree[color[1]].c(1)->mxv);
		
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &cmd, &u);
			if (cmd == 0) {
				int a = color[u];
				printf("%d\n", tree[a].max_connect(tree[a].c(u)));
			} else if (cmd == 1) {
				int a = color[u], b = color[u]^1;
				tree[a].cut(tree[a].c(u));
				color[u] ^= 1;
				tree[b].link(tree[b].c(u), tree[b].c(fa[u]));
			} else {
				scanf("%d", &v);
				tree[0].change(tree[0].c(u), v);
				tree[1].change(tree[1].c(u), v);
			}
		}
	}
	return 0;
}
