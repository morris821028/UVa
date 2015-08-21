#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 400005;
const int SEED = 13;
unsigned long BASE[MAXN];
class SPLAY_TREE { // Splay Tree
public:
	static const int MAXN = 400005;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev;
		int val, size;
		unsigned long h[2];
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			val = 0, size = 1;
			h[0] = h[1] = 0;
		}
		bool is_root() {
			return fa->ch[0] != this && fa->ch[1] != this;
		}
		void pushdown() {
			if (rev) {
				if (ch[0] != EMPTY)	ch[0]->rev ^= 1;
				if (ch[1] != EMPTY)	ch[1]->rev ^= 1;
				swap(ch[0], ch[1]), swap(h[0], h[1]);
				rev ^= 1;
			}
		}
		void pushup() {
			if (ch[0] != EMPTY)	ch[0]->pushdown();
			if (ch[1] != EMPTY)	ch[1]->pushdown();
			h[0] = ch[0]->h[0] + val*BASE[ch[0]->size] + ch[1]->h[0]*BASE[ch[0]->size+1];
        	h[1] = ch[1]->h[1] + val*BASE[ch[1]->size] + ch[0]->h[1]*BASE[ch[1]->size+1];
			size = 1 + ch[0]->size + ch[1]->size;
		}
	} _mem[MAXN];
	
	int bufIdx;
	SPLAY_TREE::Node *root;
	SPLAY_TREE() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
		Node::EMPTY->size = Node::EMPTY->val = 0;
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
		y->pushup();
	}
	void deal(Node *x) {
		if (!x->is_root())	deal(x->fa);
		x->pushdown();
	}
	Node* find_rt(Node *x) {
		for (; x->fa != Node::EMPTY; x = x->fa);
		return x;
	}
	void splay(Node *x, Node *below) {
		Node *y, *z;
		deal(x);
		while (!x->is_root() && x->fa != below) {
			y = x->fa, z = y->fa;
			if (!y->is_root() && y->fa != below) {
				if (y->ch[0] == x ^ z->ch[0] == y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
		x->pushup();
		if (x->fa == Node::EMPTY)	root = x;
	}
	Node* build(int l, int r, Node *p, char s[]) {
		if (l > r)	return Node::EMPTY; 
		int mid = (l + r)/2;
		Node *t = newNode();
		t->val = s[mid], t->fa = p;
		t->ch[0] = build(l, mid-1, t, s);
		t->ch[1] = build(mid+1, r, t, s);
		t->pushup();
		if (p == Node::EMPTY)	root = t;
		return t;
	}
	void debug(Node *u){
        if (u == Node::EMPTY) return;
        u->pushdown();
        debug(u->ch[0]);
        printf("%d", u->val);
        debug(u->ch[1]);
    }
    Node* kthNode(int pos) {
    	Node *u = root;
    	for (int t; u != Node::EMPTY;) {
    		u->pushdown();
    		t = u->ch[0]->size;
    		if (t+1 == pos)	return u;
    		if (t >= pos)
    			u = u->ch[0];
    		else
    			pos -= t+1, u = u->ch[1];
    	}
    	return Node::EMPTY;
    } 
    void insert(int pos, int val) {
    	Node *p, *q, *r;
    	p = kthNode(pos), q = kthNode(pos+1);
    	r = newNode();
    	splay(p, Node::EMPTY);
    	splay(q, root);
    	r->val = val, q->ch[0] = r, r->fa = q;
    	splay(r, Node::EMPTY);
    }
    void erase(int pos) {
    	Node *p, *q;
    	p = kthNode(pos-1), q = kthNode(pos+1);
    	splay(p, Node::EMPTY), splay(q, root);
    	q->ch[0] = Node::EMPTY;
    	splay(q, Node::EMPTY);
    }
    void reverse(int l, int r) {
    	Node *p, *q;
    	p = kthNode(l-1), q = kthNode(r+1);
    	splay(p, Node::EMPTY), splay(q, root);
    	q->ch[0]->rev ^= 1;
    	splay(q->ch[0], Node::EMPTY);
    }
    unsigned long hash(int l, int r) {
    	Node *p, *q;
    	p = kthNode(l-1), q = kthNode(r+1);
    	splay(p, Node::EMPTY), splay(q, root);
    	return q->ch[0]->h[0];
    }
    int lcp(int l, int r) {
    	int ret = 0;
    	int bl = 1, br = root->size - max(l, r), mid;
    	while (bl <= br) {
    		mid = (bl + br)/2;
    		if (hash(l, l+mid-1) == hash(r, r+mid-1))
    			bl = mid+1, ret = mid;
    		else
    			br = mid-1;
    	}
    	return ret;
    }
} tree;
SPLAY_TREE::Node *SPLAY_TREE::Node::EMPTY;
int main() {
	BASE[0] = 1;
	for (int i = 1; i < MAXN; i++)
		BASE[i] = BASE[i-1] * SEED;
	int n, m;
	int cmd, p, c, p1, p2;
	char s[262144];
	while (scanf("%d %d", &n, &m) == 2) {
		scanf("%s", s+1);
		s[0] = 3, s[n+1] = 4;
		for (int i = 1; i <= n; i++)
			s[i] -= '0';
		tree.init();
		tree.build(0, n+1, SPLAY_TREE::Node::EMPTY, s);
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &p, &c);
				tree.insert(p+1, c);
			} else if (cmd == 2) {
				scanf("%d", &p);
				tree.erase(p+1);
			} else if (cmd == 3) {
				scanf("%d %d", &p1, &p2);
				tree.reverse(p1+1, p2+1);
			} else if (cmd == 4) {
				scanf("%d %d", &p1, &p2);
				int t = tree.lcp(p1+1, p2+1);
				printf("%d\n", t);
			} 
//    		tree.debug(tree.root);
//			puts("");
		}
	}
	return 0;
}
/*
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3
*/
