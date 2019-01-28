#include <bits/stdc++.h> 
using namespace std;

struct Mesh {
static const int MAXN = 100005;
	int pt[MAXN][2];
	void read(int n) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &pt[i][0], &pt[i][1]);
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
		if (p != EMPTY)
			p->ch[i] = u;
		if (u != EMPTY)
			u->fa = p;
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
	Node* findPos(int pos) { // [0, size-1]
		for (Node *u = root; u != EMPTY;) {
			pushdown(u);
			int t = u->ch[0]->size;
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
		Node *x = newNode(); x->data = data;
		if (p == EMPTY) {
			p = maxNode(root), splay(p, EMPTY);
			setch(x, p, 0);
		} else {
			splay(p, EMPTY);
			setch(x, p->ch[0], 0), setch(x, p, 1);
			setch(p, EMPTY, 0);
			splay(p, EMPTY);
		}
		p = prevNode(x), q = nextNode(x);
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
		free(x);
		if (p == EMPTY)	p = maxNode(root);
		if (q == EMPTY)	q = minNode(root);
		return make_tuple(p->data, del, q->data);
	}
	int size() {
		return root == EMPTY ? 0 : root->size;
	}
} mlist;

static inline int log2int(int x){
	return 31 - __builtin_clz(x);
}

struct KDBRH {
static constexpr double ALPHA = 0.75;
static constexpr double LOG_ALPHA = log2(1.0 / ALPHA);
	struct Pt {
		int d[2];
		Pt() {}
		Pt(int xy[]):Pt(xy[0], xy[1]) {}
		Pt(int x, int y) {d[0] = x, d[1] = y;}
		bool operator==(const Pt &x) const {
			return d[0] == x.d[0] && d[1] == x.d[1];
		}
		static Pt NaN() {return Pt(INT_MIN, INT_MIN);}
		int isNaN() {return d[0] == INT_MIN;}
	};
	struct cmpAxis {
		int k;
		cmpAxis(int k): k(k) {}
		bool operator() (const pair<Pt, Pt> &x, const pair<Pt, Pt> &y) const {
			return x.first.d[k] < y.first.d[k];
		}
	};
	struct BBox {
#define KDMIN(a, b, c) {a[0] = min(b[0], c[0]), a[1] = min(b[1], c[1]);}
#define KDMAX(a, b, c) {a[0] = max(b[0], c[0]), a[1] = max(b[1], c[1]);}
		int l[2], r[2];
		BBox() {}
		BBox(int a[], int b[]) {
			KDMIN(l, a, b); KDMAX(r, a, b);
		}
		void expand(Pt p) {
			KDMIN(l, l, p.d); KDMAX(r, r, p.d);
		}
		void expand(BBox b) {
			KDMIN(l, l, b.l); KDMAX(r, r, b.r);
		}
		inline int raycast(double x, double fx, double y) {
			return l[1] <= y && y <= r[1] && r[0] >= x && l[0] <= fx;
		}
		static BBox init() {
			BBox b; b.l[0] = b.l[1] = INT_MAX, b.r[0] = b.r[1] = INT_MIN;
			return b;
		}
	};
	struct Node {
		Node *lson, *rson;
		Pt pt, qt;
		BBox box;
		int size, cover; int8_t used;
		Node() {
			lson = rson = NULL;
			size = 1, used = 1;
			pt = qt = Pt::NaN();
		}
		bool hasBox() { return box.l[0] <= box.r[0]; }
		void pushup() {
			size = used, cover = 1;
			if (lson)	size += lson->size, cover += lson->cover;
			if (rson)	size += rson->size, cover += rson->cover;
		}
		void pushupBox() {
			BBox t = BBox::init();
			if (!qt.isNaN())
				t.expand(pt), t.expand(qt);
			if (lson && lson->hasBox())
				t.expand(lson->box);
			if (rson && rson->hasBox())
				t.expand(rson->box);
			box = t;
		}
		double interpolate(double y) {
			if (pt.d[1] == qt.d[1])	return pt.d[0];
			return pt.d[0] + (qt.d[0] - pt.d[0]) * (y - pt.d[1]) / (qt.d[1] - pt.d[1]);
		}
	};
	Node *root;
	vector<pair<Pt, Pt>> A;
	int64_t area;
	void init() {
		root = NULL, area = 0;
	}
	int64_t h(int p, int q) {
		return (int64_t) mesh.pt[p][0]*mesh.pt[q][1] - (int64_t) mesh.pt[p][1]*mesh.pt[q][0];
	}
	void insert(tuple<int, int, int> e) {
		int p, q, r; tie(p, q, r) = e;
		insert(root, 0, Pt(mesh.pt[q]), log2int(size()) / LOG_ALPHA);
		changeNode(root, 0, Pt(mesh.pt[q]), Pt(mesh.pt[p]));
		changeNode(root, 0, Pt(mesh.pt[r]), Pt(mesh.pt[q]));
		area += h(p, q) + h(q, r) - h(p, r);
	}
	void remove(tuple<int, int, int> e) {
		int p, q, r; tie(p, q, r) = e;
		remove(root, 0, Pt(mesh.pt[q]), log2int(size()) / LOG_ALPHA);
		changeNode(root, 0, Pt(mesh.pt[r]), Pt(mesh.pt[p]));
		area -= h(p, q) + h(q, r) - h(p, r);
	}
	int RAY_PASS, RAY_T;
	double RAY_X;
	vector<double> X;
	int inside(double x, double y) {
		if (area == 0)
			return 0;
		int test = 0; RAY_PASS = 0;
		X.clear(), RAY_X = 1e+12, RAY_T = -1;
		raycast(root, 0, test, x, y);
		if (test > 32 && size() > 32 && test > size()/4)
			rebuild(root, 0);
		RAY_PASS = 0;
		if (RAY_T < 0) {
			RAY_PASS = X.size();
		} else {
			for (auto x : X)
				RAY_PASS += x <= RAY_X;
			if ((area > 0) == RAY_T)
				RAY_PASS++;
			if (area == 0)
				RAY_PASS = 0; 
		}
		return RAY_PASS&1;
	}
	int size() {
		return root == NULL ? 0 : root->size;
	}
	inline int isbad(Node *u) {
		if (u->lson && u->lson->size > u->size * ALPHA) return 1;
		if (u->rson && u->rson->size > u->size * ALPHA) return 1;
		return 0;
	}
	Node* newNode()  { return new Node(); }
	Node* build(int k, int l, int r) {
		if (l > r)	return NULL;
		int mid = (l + r)>>1;
		Node *ret = newNode();
		sort(A.begin()+l, A.begin()+r+1, cmpAxis(k));
		while (mid < r && A[mid].first.d[k] == A[mid+1].first.d[k])
			mid++;
		tie(ret->pt, ret->qt) = A[mid];
		ret->lson = build(!k, l, mid-1);
		ret->rson = build(!k, mid+1, r);
		ret->pushup(), ret->pushupBox();
		return ret;
	}
	void flatten(Node *u) {
		if (!u)	return ;
		flatten(u->lson);
		if (u->used)	A.emplace_back(u->pt, u->qt);
		flatten(u->rson);
		free(u);
	}
	void changeNode(Node *u, int k, Pt x, Pt qt) {
		if (!u)	return;
		if (x == u->pt) {
			u->qt = qt, u->pushupBox();
			return;
		}
		changeNode(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, !k, x, qt);
		u->pushupBox();
	}
	void rebuild(Node* &u, int k) {
		A.clear(), A.reserve(u->size);
		flatten(u);
		u = build(k, 0, A.size()-1);
	}
	bool insert(Node* &u, int k, Pt x, int d) {
		if (!u) {
			u = newNode(), u->pt = x, u->pushupBox();
			return d <= 0;
		}
		if (x == u->pt) {
			u->used = 1, u->pushup(), u->pushupBox();
			return d <= 0;
		}
		int t = insert(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, !k, x, d-1);
		u->pushup(), u->pushupBox();
		if (t && !isbad(u))
			return 1;
		if (t)	rebuild(u, k);
		return 0;
	}
	bool remove(Node* &u, int k, Pt x, int d) {
		if (!u)
			return d <= 0;
		if (x == u->pt) {
			u->used = 0, u->qt = Pt::NaN(), u->pushup(), u->pushupBox();
			return d <= 0;
		}
		int t = remove(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, !k, x, d-1);
		u->pushup(), u->pushupBox();
		if (t && !isbad(u))
			return 1;
		if (t)	rebuild(u, k);
		return 0;
	}
	int raycast(Node *u, double x, double y) {
		if (u->qt.isNaN() || (u->pt.d[1] > y) == (u->qt.d[1] > y))
			return 0;
		double tx = u->interpolate(y);
		assert(tx < 1e+12);
		if (x >= tx || tx > RAY_X)
			return 0;
		if (u->pt.d[1] != u->qt.d[1]) {
			RAY_X = min(RAY_X, tx);
			RAY_T = u->pt.d[1] < u->qt.d[1];
		}
		X.push_back(tx);
		return 1;
	}
	void raycast(Node* &u, int k, int &test, double x, double y) {
		if (!u || !u->box.raycast(x, RAY_X, y))
			return;
		RAY_PASS += raycast(u, x, y);
		raycast(u->lson, !k, test, x, y);
		raycast(u->rson, !k, test, x, y);
		test++;
	}
} mbrh;

int main() {
	int n, m;
	int cmd, x, pos;
	double px, py;
	scanf("%d %d", &n, &m);
	mesh.read(n);
	mlist.init(), mbrh.init();
	int cases = 0;
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
			int ret = mbrh.inside(px, py);
			puts(ret ? "1" : "0");
		}
	}
	return 0;
}
