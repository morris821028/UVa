#include <bits/stdc++.h> 
using namespace std;

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
    return u;
}
Node* maxNode(Node *u) {
	splay(u, EMPTY);
    for (; pushdown(u), u->ch[1] != EMPTY; u = u->ch[1]);
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
			splay(x, EMPTY);
		} 
		goto DONE;
	}
	if (p->ch[0] == EMPTY)
		p->ch[0] = x, x->fa = p;
	else
		q = prevNode(p), q->ch[1] = x, x->fa = q;
	splay(x, EMPTY);
	DONE:
	p = prevNode(x), q = nextNode(x);
	if (p == EMPTY)	p = maxNode(root);
	if (q == EMPTY)	q = minNode(root);
	return make_tuple(p->data, data, q->data);
}
tuple<int, int, int> remove(int pos) {
	Node *x = findPos(pos);
	Node *p, *q, *l, *r;
	p = prevNode(x), splay(p, x);
	q = nextNode(x), splay(q, x);
	if (p == EMPTY)	p = maxNode(root);
	if (q == EMPTY)	q = minNode(root);
	auto ret = make_tuple(p->data, x->data, q->data);
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
	free(x);
	return ret;
}
} mlist;

struct Mesh {
	static const int MAXN = 100005;
	int pt[MAXN][2];
	void read(int n) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &pt[i][0], &pt[i][1]);
	}
} mesh;

static int log2int(int x){
    return 31 - __builtin_clz(x);
}

class KDBRH {
static constexpr double ALPHA = 0.75;
static constexpr double LOG_ALPHA = log2(1.0 / ALPHA);
static const int MAXM = 200000;
public:
struct Pt {
    int *d;
    Pt() {}
    Pt(int xy[]) {d = xy; }
    bool operator==(const Pt &x) const {
    	return d[0] == x.d[0] && d[1] == x.d[1];
	}
};
struct cmpAxis {
	int k;
	cmpAxis(int k): k(k) {}
	bool operator() (const pair<Pt, Pt> &x, const pair<Pt, Pt> &y) const {
		return x.first.d[k] < y.first.d[k];
	}
};
struct BBox {
	int l[2], r[2];
	BBox() {}
	BBox(int a[], int b[]) {
		for (int i = 0; i < 2; i++)
			l[i] = min(a[i], b[i]), r[i] = max(a[i], b[i]);
	}
	static BBox merge(BBox a, BBox b) {
		BBox ret;
		for (int i = 0; i < 2; i++)
			ret.l[i] = min(a.l[i], b.l[i]), ret.r[i] = max(a.r[i], b.r[i]);
		return ret;
	}
	static BBox init() {
		BBox ret;
		ret.l[0] = INT_MAX, ret.l[1] = INT_MAX, ret.r[0] = INT_MIN, ret.r[1] = INT_MIN;
		return ret;
	}
	void expand(Pt p) {
		for (int i = 0; i < 2; i++)
			l[i] = min(l[i], p.d[i]), r[i] = max(r[i], p.d[i]);
	}
	int raycast(double x, double y) {
		return !(r[0] < x || l[1] > y || r[1] < y);
	}
};
struct Node {
    Node *lson, *rson;
    Pt pt; Pt qt;
    BBox box;
    int size; int8_t used;
    Node() {
    	lson = rson = NULL;
    	size = 1, used = 1;
    	pt.d = qt.d = NULL;
    }
    bool hasBox() { return box.l[0] <= box.r[0]; }
    void pushup() {
    	size = used;
    	if (lson)	size += lson->size;
    	if (rson)	size += rson->size;
    }
    void pushupBox() {
    	BBox t;
    	if (qt.d)
    		t = BBox(pt.d, qt.d);
    	else
    		t = BBox::init();
    	if (lson && lson->hasBox())
    		t = BBox::merge(t, lson->box);
    	if (rson && rson->hasBox())
    		t = BBox::merge(t, rson->box);
    	box = t;
    }
	double interpolate(double y) {
		if (pt.d[1] == qt.d[1])	return pt.d[0];
		return pt.d[0] + (qt.d[0] - pt.d[0]) * (y - pt.d[1]) / (qt.d[1] - pt.d[1]);
	}
    int raycast(double x, double y) {
    	return qt.d && (pt.d[1] > y) != (qt.d[1] > y) && x < interpolate(y);
	}
};
Node *root;
pair<Pt, Pt> A[MAXM];
void init() {
	root = NULL;
}
void insert(tuple<int, int, int> e) {
	int p, q, r;
	tie(p, q, r) = e;
	insert(root, 0, Pt(mesh.pt[q]), log2int(size()) / LOG_ALPHA);
	changeNode(root, 0, Pt(mesh.pt[q]), mesh.pt[p]);
	changeNode(root, 0, Pt(mesh.pt[r]), mesh.pt[q]);
}
void remove(tuple<int, int, int> e) {
	int p, q, r;
	tie(p, q, r) = e;
	remove(root, 0, Pt(mesh.pt[q]), log2int(size()) / LOG_ALPHA);
	changeNode(root, 0, Pt(mesh.pt[r]), mesh.pt[p]);
}
int RAY_PASS;
int inside(double x, double y) {
	RAY_PASS = 0;
	int test = 0;
	raycast(root, 0, test, x, y);
	if (test > 32 && size() > 32 && ((double) test / size() > 0.25))
		rebuild(root, 0);
	return RAY_PASS&1;
}
int size() {
	return root == NULL ? 0 : root->size;
}
inline int isbad(Node *u) {
	if (u->lson && u->lson->size > u->size * ALPHA)
		return 1;
	if (u->rson && u->rson->size > u->size * ALPHA)
		return 1;
	return 0;
}
Node* newNode()  { return new Node(); }
Node* build(int k, int l, int r) {
	if (l > r)	return NULL;
	if (k == 2)	k = 0;
	Node *ret = newNode();
	int mid = (l + r)>>1;
	sort(A+l, A+r+1, cmpAxis(k));
	while (mid < r && A[mid].first.d[k] == A[mid+1].first.d[k])
		mid++;
	ret->pt = A[mid].first, ret->qt = A[mid].second;
    ret->lson = build(k+1, l, mid-1);
    ret->rson = build(k+1, mid+1, r);
	ret->pushup();
	ret->pushupBox();
	return ret;
}
void flatten(Node *u, pair<Pt, Pt>* &buf) {
	if (!u)	return ;
	flatten(u->lson, buf);
	if (u->used)	*buf = {u->pt, u->qt}, buf++;
	flatten(u->rson, buf);
	free(u);
}
void changeNode(Node *u, int k, Pt x, int *qtd) {
	if (!u)	return;
	if (x == u->pt) {
		u->qt.d = qtd;
		u->pushupBox();
		return;
	}
	if (k == 2)	k = 0;
	changeNode(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, k+1, x, qtd);
	u->pushupBox();
}
void rebuild(Node* &u, int k) {
	auto *ptr = &A[0];
	flatten(u, ptr);
	u = build(k, 0, (ptr-A)-1);
}
bool insert(Node* &u, int k, Pt x, int d) {
	if (!u) {
		u = newNode(), u->pt = x, u->qt.d = NULL;
		u->pushupBox();
		return d <= 0;
	}
	if (x == u->pt) {
		u->used = 1;
		u->pushupBox();
		return d <= 0;
	}
	if (k == 2)	k = 0;
	int t = insert(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, k+1, x, d-1);
	u->pushup(), u->pushupBox();
	if (t && !isbad(u))
		return 1;
	if (t)
		rebuild(u, k);
	return 0;
}
bool remove(Node* &u, int k, Pt x, int d) {
	if (u == NULL)
		return d <= 0;
	if (x == u->pt) {
		u->used = 0, u->qt.d = NULL;
		return d <= 0;
	}
	if (k == 2)	k = 0;
	int t = remove(x.d[k] <= u->pt.d[k] ? u->lson : u->rson, k+1, x, d-1);
	u->pushup(), u->pushupBox();
	if (t && !isbad(u))
		return 1;
	if (t)
		rebuild(u, k);
	return 0;
}
void raycast(Node* &u, int k, int &test, double x, double y) {
	if (!u || !u->box.raycast(x, y))
		return;
	RAY_PASS += u->raycast(x, y);
	if (k == 2)	k = 0;
	raycast(u->lson, k+1, test, x, y);
	raycast(u->rson, k+1, test, x, y);
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
			printf("%d\n", mbrh.inside(px, py));
		}
	}
	return 0;
}
