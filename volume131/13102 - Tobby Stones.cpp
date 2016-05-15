#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 1048576;

class SPLAY_TREE { // Splay Tree
public:
    static const int MAXN = 1048576;
    struct Node {
        static Node *EMPTY;
        Node *ch[2], *fa;
        char rev, set, inv, val;
        int size;
        int sumw, sumb;
        Node() {
            ch[0] = ch[1] = fa = NULL;
            rev = set = inv = 0;
            val = sumw = sumb = 0, size = 1;
        }
        bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }
        void pushdown() {
            if (rev) {
                if (ch[0] != EMPTY)	ch[0]->rev ^= 1;
                if (ch[1] != EMPTY)	ch[1]->rev ^= 1;
                swap(ch[0], ch[1]);
                rev ^= 1;
            }
            if (set) {
            	if (ch[0] != EMPTY)	ch[0]->set = set, ch[0]->inv = 0;
                if (ch[1] != EMPTY)	ch[1]->set = set, ch[1]->inv = 0;
                if (set == 1)	 // white
                	val = 0, sumw = sumw + sumb, sumb = 0;
				else
					val = 1, sumb = sumw + sumb, sumw = 0;
                set = 0, inv = 0;
			}
			if (inv) {
				if (ch[0] != EMPTY) {
					if (ch[0]->set)	
						ch[0]->set = 3 - ch[0]->set;
					else
						ch[0]->inv ^= 1;
				}
                if (ch[1] != EMPTY)	{
                	if (ch[1]->set)
                		ch[1]->set = 3 - ch[1]->set;
                	else
						ch[1]->inv ^= 1;
				}
                swap(sumw, sumb), val = !val;
                inv = 0;
			}
        }
        void pushup() {
            if (ch[0] != EMPTY)	ch[0]->pushdown();
            if (ch[1] != EMPTY)	ch[1]->pushdown();
            sumw = sumb = 0;
            if (val == 0)	sumw++;
            else			sumb++;
            sumw += ch[0]->sumw + ch[1]->sumw;
            sumb += ch[0]->sumb + ch[1]->sumb;
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
        if (t->val == 0)	t->sumw ++;
        else				t->sumb ++;
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
    	p = kthNode(l), q = kthNode(r+2);
    	splay(p, Node::EMPTY), splay(q, root);
    	q->ch[0]->rev ^= 1;
    	splay(q->ch[0], Node::EMPTY);
    }
    void inverse(int l, int r) {
    	Node *p, *q;
    	p = kthNode(l), q = kthNode(r+2);
    	splay(p, Node::EMPTY), splay(q, root);
    	q->ch[0]->inv ^= 1;
    	splay(q->ch[0], Node::EMPTY);
	}
	void reset(int l, int r, int c) {
		Node *p, *q;
    	p = kthNode(l), q = kthNode(r+2);
    	splay(p, Node::EMPTY), splay(q, root);
    	if (c == 1) {
    		q->ch[0]->set = 1;
		} else {
			q->ch[0]->set = 2;
		}
    	splay(q->ch[0], Node::EMPTY);
	}
    pair<int, int> stat(int l, int r) {
    	Node *p, *q;
    	p = kthNode(l), q = kthNode(r+2);
    	splay(p, Node::EMPTY), splay(q, root);
    	return make_pair(q->ch[0]->sumb, q->ch[0]->sumw);
	}
	
} tree;
SPLAY_TREE::Node *SPLAY_TREE::Node::EMPTY;

int main() {
    static char s[1048576] = {}; // white
    int n, m, cmd, l, r, c;
    while (scanf("%d %d", &n, &m) == 2) {
    	for (int i = 0; i <= n+1; i++)
    		s[i] = 0;
    	tree.init();
    	tree.build(0, n+1, SPLAY_TREE::Node::EMPTY, s);
    	pair<int, int> ret;
    	for (int i = 0; i < m; i++) {
    		scanf("%d", &cmd);
    		if (cmd == 0) {
    			scanf("%d %d", &l, &r);
    			ret = tree.stat(l+1, r+1);
    			printf("%d %d\n", ret.first, ret.second);
			} else if (cmd == 1) {
				scanf("%d %d", &l, &r);
				tree.reverse(l+1, r+1);
			} else if (cmd == 2) {
				scanf("%d %d", &l, &r);
				tree.inverse(l+1, r+1);
			} else if (cmd == 3) {
				scanf("%d %d %d", &l, &r, &c);
				tree.reset(l+1, r+1, c);
			}
		}
	}
    return 0;
}
