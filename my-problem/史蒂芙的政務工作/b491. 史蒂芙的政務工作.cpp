#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 200005;
class SPLAY_TREE { // Splay Tree
public:
	static const int MAXN = 200005;
	struct Node {
		static Node *EMPTY;
		Node *ch[2], *fa;
		int rev, size;
		int L, R, LRsize;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			rev = 0;
			size = 1;
			L = 0, R = -1, LRsize = 0;
		}
		bool is_root() {
			return fa->ch[0] != this && fa->ch[1] != this;
		}
		void pushdown() {
			if (rev) {
				if (ch[0] != EMPTY)	ch[0]->rev ^= 1;
				if (ch[1] != EMPTY)	ch[1]->rev ^= 1;
				swap(ch[0], ch[1]), swap(L, R);
				rev ^= 1;
			}
		}
		void pushup() {
			if (ch[0] != EMPTY)	ch[0]->pushdown();
			if (ch[1] != EMPTY)	ch[1]->pushdown();
			size = 1 + ch[0]->size + ch[1]->size;
			LRsize = i_size() + ch[0]->LRsize + ch[1]->LRsize;
		}
		inline int i_size() {
			if (this == EMPTY)	return 0;
			return max(R, L) - min(R, L) + 1;
		}
	} _mem[MAXN];
	
	int bufIdx;
	SPLAY_TREE::Node *root;
	map<int, Node*> S;
	SPLAY_TREE() {
		Node::EMPTY = &_mem[0];
		Node::EMPTY->fa = Node::EMPTY->ch[0] = Node::EMPTY->ch[1] = Node::EMPTY;
		Node::EMPTY->size = 0;
		bufIdx = 1; 
	}
	void init() {
		bufIdx = 1;
		S.clear();
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
		if (x == Node::EMPTY)	return ;
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
	Node* build(int l, int r) {
		if (l > r)	return Node::EMPTY; 
		Node *t = newNode();
		t->L = l, t->R = r;
		t->fa = Node::EMPTY;
		t->pushup();
		root = t;
		S[min(l, r)] = t;
		return t;
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
    			u = u->ch[1], pos -= t+1;
    	}
    	return Node::EMPTY;
    }
    Node *splitNode(int pos) {	// make node interval [pos, ?]
    	Node *u = root, *v;
    	for (int t; u != Node::EMPTY;) {
    		u->pushdown();
    		t = u->ch[0]->LRsize;
    		if (t+1 == pos)	return u; 
    		if (t >= pos) {
    			u = u->ch[0];
    		} else if (pos > t + u->i_size()) {
    			pos -= t + u->i_size(), u = u->ch[1];
    		} else {
				int l = u->L, r = u->R;
    			Node *x = newNode();
    			splay(u, Node::EMPTY);
    			u->pushdown();
    			pos -= t;
    			S[min(u->L, u->R)] = u;
    			if (l < r)
    				u->L = l + (pos - 1), r = u->L - 1;
    			else
    				u->L = l - (pos - 1), r = u->L + 1;
    			u->pushup();
    			x->L = l, x->R = r, x->pushup();
    			if (u->ch[0] == Node::EMPTY) {
    				u->ch[0] = x, x->fa = u;
    				u->pushup();
    			} else {
    				for (v = u->ch[0]; v->pushdown(), v->ch[1] != Node::EMPTY; v = v->ch[1]);
    				v->ch[1] = x, x->fa = v;
    				splay(v, Node::EMPTY);
    			}
    			S[min(u->L, u->R)] = u;
    			S[min(x->L, x->R)] = x;
    			return u;
    		}
    	}
    }
    void reverse(int l, int r) {
    	Node *p, *q;
    	p = splitNode(l);
    	splay(p, Node::EMPTY);
    	p = kthNode(p->ch[0]->size);
		q = splitNode(r+1);
    	splay(p, Node::EMPTY), splay(q, root);
    	q->ch[0]->rev ^= 1;
    	splay(q->ch[0], Node::EMPTY);
    }
    int find(int x) {
    	Node *u;
    	map<int, Node*>::iterator it;
		it = S.upper_bound(x), it--;
    	u = it->second;
    	splay(u, Node::EMPTY);
    	return u->ch[0]->LRsize + abs(x - u->L) + 1;
    }
    void debug(Node *u) {
        if (u == Node::EMPTY) return;
        u->pushdown();
        debug(u->ch[0]);
        printf("[%d %d]", u->L, u->R);
        debug(u->ch[1]);
    }
} tree;
SPLAY_TREE::Node *SPLAY_TREE::Node::EMPTY;

int main() {
	int N, Q;
	int cmd, l, r, x;
	while (scanf("%d %d", &N, &Q) == 2) {
		tree.init();
		tree.build(0, N+1);	// value [0, N+1], index [1, N+2]
		for (int i = 0; i < Q; i++) {
			scanf("%d", &cmd);
			if (cmd == 0) {
				scanf("%d %d", &l, &r);
				tree.reverse(l+1, r+1);
			} else {
				scanf("%d", &x);
				printf("%d\n", tree.find(x) - 1);
			} 
		}
	}
	return 0;
}
/*
7 6
1 7
0 3 5
1 5
0 1 3
1 3
1 1

5 5
0 1 3
0 4 5
1 1
1 3
1 5

5 5
0 1 4
0 2 5
1 1
1 3
1 5
*/
