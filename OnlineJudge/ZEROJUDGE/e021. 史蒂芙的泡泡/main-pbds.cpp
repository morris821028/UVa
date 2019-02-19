#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

struct Mesh {
static const int MAXN = 1e5 + 5;
	int pt[MAXN][2];
	vector<int> X;
	void read(int n) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &pt[i][0], &pt[i][1]);
		X.clear(); X.reserve(n);
		for (int i = 0; i < n; i++)
			X.push_back(pt[i][0]);
		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());
	}
} mesh;

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
	Node *root, *EMPTY;
	void pushdown(Node *u) {}
	void pushup(Node *u) {
		if (u->ch[0] != EMPTY)	pushdown(u->ch[0]);
		if (u->ch[1] != EMPTY)	pushdown(u->ch[1]);
		u->size = 1 + u->ch[0]->size + u->ch[1]->size;
	}
	void setch(Node *p, Node *u, int i) {
		if (p != EMPTY)	p->ch[i] = u;
		if (u != EMPTY)	u->fa = p;
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
		return maxNode(u->ch[0]);
	}
	Node* nextNode(Node *u) {
		splay(u, EMPTY);
		return minNode(u->ch[1]);
	}
	Node* minNode(Node *u) {
		Node *p = u->fa;
		for (; pushdown(u), u->ch[0] != EMPTY; u = u->ch[0]);
		splay(u, p);
		return u;
	}
	Node* maxNode(Node *u) {
		Node *p = u->fa;
		for (; pushdown(u), u->ch[1] != EMPTY; u = u->ch[1]);
		splay(u, p);
		return u;
	}
	Node* findPos(int pos) { // [0...]
		for (Node *u = root; u != EMPTY;) {
			pushdown(u);
			int t = u->ch[0]->size;
			if (t == pos) {
				splay(u, EMPTY);
				return u;
			}
			if (t > pos)
				u = u->ch[0];
			else
				u = u->ch[1], pos -= t + 1;
		}
		return EMPTY;
	}
	tuple<int, int, int> insert(int data, int pos) {	// make [pos] = data
		Node *p, *q = findPos(pos);
		Node *x = newNode(); x->data = data;
		if (q == EMPTY) {
			p = maxNode(root), splay(p, EMPTY);
			setch(x, p, 0);
			splay(x, EMPTY);
		} else {
			splay(q, EMPTY), p = q->ch[0];
			setch(x, p, 0), setch(x, q, 1);
			setch(q, EMPTY, 0);
			splay(q, EMPTY);
			p = prevNode(x);
		}
		if (p == EMPTY)	p = maxNode(root);
		if (q == EMPTY)	q = minNode(root);
		return make_tuple(p->data, data, q->data);
	}
	tuple<int, int, int> remove(int pos) {
		Node *x = findPos(pos), *p, *q;
		p = prevNode(x), q = nextNode(x);
		if (p != EMPTY && q != EMPTY) {
			setch(p, q, 1);
			p->fa = EMPTY, splay(q, EMPTY);
		} else if (p != EMPTY) {
			p->fa = EMPTY, root = p;
		} else {
			q->fa = EMPTY, root = q;
		}
		int del = x->data;
		delete x;
		if (p == EMPTY)	p = maxNode(root);
		if (q == EMPTY)	q = minNode(root);
		return make_tuple(p->data, del, q->data);
	}
	int size() {
		return root == EMPTY ? 0 : root->size;
	}
} mlist;

struct Pt {
	double x, y;
	Pt() {}
	Pt(int xy[]):Pt(xy[0], xy[1]) {}
	Pt(double x, double y):x(x), y(y) {}
	bool operator<(const Pt &o) const {
		if (x != o.x)	return x < o.x;
		return y < o.y;
	}
};

struct PtP {
	static double x;
	Pt p, q;
	PtP(Pt a, Pt b) {
		p = a, q = b;
		if (q < p)
			swap(p, q);
	}
	double interpolate(const Pt& p1, const Pt& p2, double& x) const {
        if (p1.x == p2.x) return min(p1.y, p2.y);
        return p1.y + (p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
	bool operator<(const PtP &o) const {
		return interpolate(p, q, x) < interpolate(o.p, o.q, x);
	}
};
double PtP::x = 1;

struct SegSeg {
	struct Node {
		Node *lson, *rson;
		tree<pair<PtP, int>, null_type, less<pair<PtP, int>>, rb_tree_tag, tree_order_statistics_node_update> segs;
		Node() {
			lson = rson = NULL;
		}
	};
	Node *root;
	int xn;
	Node* newNode() {
		return new Node();
	}
	void freeNode(Node *u) {
		free(u);
	}
	void init() {
		root = NULL;
		xn = mesh.X.size();
	}
	void insert(tuple<int, int, int> e) {
		int p, q, r; tie(p, q, r) = e;
		remove(0, xn-1, {PtP(Pt(mesh.pt[p]), Pt(mesh.pt[r])), r});
		insert(0, xn-1, {PtP(Pt(mesh.pt[p]), Pt(mesh.pt[q])), q});
		insert(0, xn-1, {PtP(Pt(mesh.pt[q]), Pt(mesh.pt[r])), r});
	}
	void remove(tuple<int, int, int> e) {
		int p, q, r; tie(p, q, r) = e;
		remove(0, xn-1, {PtP(Pt(mesh.pt[p]), Pt(mesh.pt[q])), q});
		remove(0, xn-1, {PtP(Pt(mesh.pt[q]), Pt(mesh.pt[r])), r});
		insert(0, xn-1, {PtP(Pt(mesh.pt[p]), Pt(mesh.pt[r])), r});
	}	
	int inside(double x, double y) {
		PtP::x = x;
		return count(root, 0, xn-1, x, y)&1;
	}
	int count(Node* u, int l, int r, double x, double y) {
		if (u == NULL)
			return 0;
		int ret = 0;
		if ((mesh.X[l] > x) != (mesh.X[r] > x))
			ret += u->segs.order_of_key({PtP(Pt(x, y), Pt(x, y)), -1});
		int m = (l+r)/2;
		if (x <= mesh.X[m])
			ret += count(u->lson, l, m, x, y);
		if (x >= mesh.X[m])
			ret += count(u->rson, m, r, x, y);
		return ret;
	}
	void insert(int l, int r, pair<PtP, int> s) {
		if (s.first.p.x != s.first.q.x)
			insert(root, l, r, s);
	}
	void remove(int l, int r, pair<PtP, int> s) {
		if (s.first.p.x != s.first.q.x)
			remove(root, l, r, s);
	}
	void insert(Node* &u, int l, int r, pair<PtP, int> s) {
		if (u == NULL)
			u = newNode();
		if (s.first.p.x <= mesh.X[l] && mesh.X[r] <= s.first.q.x) {
			PtP::x = (mesh.X[l] + mesh.X[r])/2.0;
			u->segs.insert(s);
			return;
		}
		int m = (l+r)/2;
		if (s.first.q.x <= mesh.X[m])			insert(u->lson, l, m, s);
		else if (s.first.p.x >= mesh.X[m])	insert(u->rson, m, r, s);
		else	insert(u->lson, l, m, s), insert(u->rson, m, r, s);
	}
	void remove(Node* u, int l, int r, pair<PtP, int> s) {
		if (u == NULL)
			return;
		if (s.first.p.x <= mesh.X[l] && mesh.X[r] <= s.first.q.x) {
			PtP::x = (mesh.X[l] + mesh.X[r])/2.0;
			u->segs.erase(s);
			return;
		}
		int m = (l+r)/2;
		if (s.first.q.x <= mesh.X[m])			remove(u->lson, l, m, s);
		else if (s.first.p.x >= mesh.X[m])	remove(u->rson, m, r, s);
		else	remove(u->lson, l, m, s), remove(u->rson, m, r, s);
	}
} mbrh;

int main() {
	int n, m, cmd, x, pos;
	double px, py;
	scanf("%d %d", &n, &m);
	mesh.read(n);
	mlist.init(), mbrh.init();
	for (int i = 0; i < m; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d %d", &x, &pos);
			mbrh.insert(mlist.insert(x, pos));
		} else if (cmd == 2) {
			scanf("%d", &x);
			mbrh.remove(mlist.remove(x));
		} else {
			scanf("%lf %lf", &px, &py);
			puts(mbrh.inside(px, py) ? "1" : "0");
		}
	}
	return 0;
}
