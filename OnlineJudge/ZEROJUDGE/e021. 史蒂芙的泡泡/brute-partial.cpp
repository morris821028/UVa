#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;
struct Point {
	int x, y;
} p[MAXN];

class SplayTree {
public:
	struct Node {
	    Node *ch[2], *fa;
	    int size; int data;
	    Node() {
	        ch[0] = ch[1] = fa = NULL;
			size = 1;
	    }
	    bool is_root() {
	        return fa->ch[0] != this && fa->ch[1] != this;
	    }
	};
	SplayTree::Node *root;
	Node *EMPTY;
	void pushdown(Node *u) {}
	void pushup(Node *u) {
		if (u->ch[0] != EMPTY)	pushdown(u->ch[0]);
		if (u->ch[1] != EMPTY)	pushdown(u->ch[1]);
		u->size = 1 + u->ch[0]->size + u->ch[1]->size;
	}
	SplayTree() {
	    EMPTY = new Node();
	    EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
		EMPTY->size = 0;
	}
	void init() {
	    root = EMPTY;
	}
	Node* newNode() {
	    Node *u = new Node();
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
	    pushup(y);
	}
	void deal(Node *x) {
	    if (!x->is_root())	deal(x->fa);
	    pushdown(x);
	}
	Node* find_rt(Node *x) {
	    for (; x->fa != EMPTY; x = x->fa);
	    return x;
	}
	void splay(Node *x, Node *below) {
	    if (x == EMPTY)	return ;
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
	    pushup(x);
	    if (x->fa == EMPTY)	root = x;
	}
	Node* prevNode(Node *u) {
		splay(u, EMPTY);
	    for (u = u->ch[0]; pushdown(u), u->ch[1] != EMPTY; u = u->ch[1]);
	    return u;
	}
	Node* nextNode(Node *u) {
		splay(u, EMPTY);
	    for (u = u->ch[1]; pushdown(u), u->ch[0] != EMPTY; u = u->ch[0]);
	    return u;
	}
	Node* minNode(Node *u) {
		splay(u, EMPTY);
	    for (; pushdown(u), u->ch[0] != EMPTY; u = u->ch[0]);
	    splay(u, EMPTY);
	    return u;
	}
	Node* maxNode(Node *u) {
		splay(u, EMPTY);
	    for (; pushdown(u), u->ch[1] != EMPTY; u = u->ch[1]);
	    splay(u, EMPTY);
	    return u;
	}
	Node* findPos(int pos) {
		Node *u = root, *v;
		for (int t; u != EMPTY;) {
			pushdown(u);
			t = u->ch[0]->size;
			if (t == pos)	return u;
			if (t > pos)
				u = u->ch[0];
			else
				u = u->ch[1], pos -= t + 1;
		}
		return EMPTY;
	}
	tuple<int, int, int> insert(int data, int pos) {	// make [pos] = data
		Node *p = findPos(pos), *q;
		Node *x = newNode();
		x->data = data;
		if (p == EMPTY) {
			p = maxNode(root);
			if (p == EMPTY) { 
				root = p;
			} else {
				p->ch[1] = x, x->fa = p;
			}
		} else if (p->ch[0] == EMPTY)
			p->ch[0] = x, x->fa = p;
		else
			q = prevNode(p), q->ch[1] = x, x->fa = q;
		splay(x, EMPTY);
		p = prevNode(x), splay(p, x);
		q = nextNode(x), splay(q, x);
		if (p == EMPTY)	p = maxNode(root);
		if (q == EMPTY)	q = minNode(root);
		return make_tuple(p->data, data, q->data);
	}
	tuple<int, int, int> remove(int pos) {
		Node *x = findPos(pos);
		Node *p, *q, *l, *r;
		p = prevNode(x), splay(p, x);
		q = nextNode(x), splay(q, x);
		splay(x, EMPTY);
		p = prevNode(x), q = nextNode(x);
		if (p != EMPTY && q != EMPTY) {
			p->ch[1] = q, p->fa = EMPTY;
			q->fa = p;
			splay(q, EMPTY);
		} else if (p != EMPTY) {
			p->fa = EMPTY;
			root = p;
		} else if (q != EMPTY) {
			q->fa = EMPTY;
			root = q;
		} else {
			root = EMPTY;
		}
		int del = x->data;
		free(x);
		if (p == EMPTY)	p = maxNode(root);
		if (q == EMPTY)	q = minNode(root);
		return make_tuple(p->data, del, q->data);
	}
	int size() {
		return root == EMPTY ? 0 : root->size;
	}
	double interpolate_x(double y, Point p1, Point p2) {
    	if (p1.y == p2.y) return p1.x;
    	return p1.x + (double) (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
	}
	int prev = -1, pass;
	double tx, ty;
	void _traversal_inside(Node *u) {
		if (u == EMPTY)
			return;
		_traversal_inside(u->ch[0]);
		int i = prev, j = u->data;
		if ((p[i].y > ty) != (p[j].y > ty) &&
	    	tx < interpolate_x(ty, p[i], p[j]))
	        pass++;
	    prev = j;
		_traversal_inside(u->ch[1]);
	}
	int inside(double tx, double ty) {
		if (root == EMPTY)
			return 0;
		this->tx = tx, this->ty = ty;
		Node *mx = maxNode(root);
		prev = mx->data;
		pass = 0;
		_traversal_inside(root);
		return pass&1;
	}
} mlist;	

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		mlist.init();
		int cmd, x, pos;
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &x, &pos);
				auto tup = mlist.insert(x, pos);
			} else if (cmd == 2) {
				scanf("%d", &x);
				auto tup = mlist.remove(x);
			} else {
				double px, py;
				scanf("%lf %lf", &px, &py);
				printf("%d\n", mlist.inside(px, py));
			}
//			printf("[");
//			for (auto t : A)
//				printf("%d ", t);
//			printf("]\n");
//
//			printf("Polygon(");
//			for (int i = 0; i < A.size(); i++) {
//				printf("(%d, %d)%c", p[A[i]].x, p[A[i]].y, ",)"[i==A.size()-1]);
//			}
//			puts("");
		}
	}
	return 0;
}
