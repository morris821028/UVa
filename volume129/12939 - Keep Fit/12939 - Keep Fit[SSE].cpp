#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;
// mo's algorithm, kd tree
struct Pt {
	int xy[2], id;
	Pt(int x=0, int y=0, int id=0):
		id(id) {xy[0] = x, xy[1] = y;}
};
typedef int32_t v8si __attribute__((vector_size (16)));	// 16 bytes = 128 bits = 4-32bit

const int MAXN = 200005;
const int MAXQ = 1005;
const int MAXF = 4;
struct KdTree {
	struct VExt {
		int32_t px[MAXF], py[MAXF], val[MAXF];
	} __attribute__ ((aligned(16)));
	struct Node {
		Node *lson, *rson;
	};
	__attribute__ ((aligned(16))) VExt _dat[MAXN];
	Node *root, *loc[MAXN];
	Node _nodes[MAXN];
	Node *p[MAXN];
	int sum[MAXN];
	int nodeIdx;
	Pt A[MAXN];
	int lx, ly, rx, ry;
	static bool cmp0(const Pt &x, const Pt &y) {
		return x.xy[0] < y.xy[0];
	}
	static bool cmp1(const Pt &x, const Pt &y) {
		return x.xy[1] < y.xy[1];
	}
	static bool icmp(const Pt &x, const Pt &y) {
		return x.id < y.id;
	}
	Node* _build(int k, int l, int r, Node *fa) {
		if (l > r)
			return NULL;
		int m = (l+r)>>1;
		Node *ret = &_nodes[nodeIdx++];
		nth_element(A+l, A+m, A+r+1, k ? cmp1 : cmp0);
		while (m < r && A[m].xy[k] == A[m+1].xy[k])
			m++;
		int idx = ret-_nodes;
		int n = min(MAXF, m-l+1);
		p[idx] = fa;
		sum[idx] = 0;
		memset(_dat[idx].val, 0, sizeof(_dat[idx].val));
		for (int i = 0; i < n; i++) {
			_dat[idx].px[i] = A[m-i].xy[0], _dat[idx].py[i] = A[m-i].xy[1];
			loc[A[m-i].id] = ret;
		}
		ret->lson = _build(!k, l, m-n, ret);
		ret->rson = _build(!k, m+1, r, ret);
		return ret;
	}
	void build(int n) {
		lx = rx = A[0].xy[0], ly = ry = A[0].xy[1];
		for (int i = 1; i < n; i++) {
			lx = min(lx, A[i].xy[0]), rx = max(rx, A[i].xy[0]);
			ly = min(ly, A[i].xy[1]), ry = max(ry, A[i].xy[1]);
		}
		nodeIdx = 0;
		root = _build(0, 0, n-1, NULL);
		sort(A, A+n, icmp);
	}
	void inc(int i) {
		Node *fa = loc[i];
		int x = A[i].xy[0], y = A[i].xy[1];
		for (int i = 0; i < MAXF; i++) {
			if (_dat[fa-_nodes].px[i] == x && _dat[fa-_nodes].py[i] == y) {
				_dat[fa-_nodes].val[i] = 1;
				break;
			}
		}
		fa = p[fa-_nodes];
		while (fa != NULL)
			sum[fa-_nodes]++, fa = p[fa-_nodes];
	}
	void dec(int i) {
		Node *fa = loc[i];
		int x = A[i].xy[0], y = A[i].xy[1];
		for (int i = 0; i < MAXF; i++) {
			if (_dat[fa-_nodes].px[i] == x && _dat[fa-_nodes].py[i] == y) {
				_dat[fa-_nodes].val[i] = 0;
				break;
			}
		}
		fa = p[fa-_nodes];
		while (fa != NULL)
			sum[fa-_nodes]--, fa = p[fa-_nodes];
	}
	static int qlx, qly, qrx, qry, qret;
	__attribute__ ((aligned(16))) static v8si v8ret;
	__attribute__ ((aligned(16))) static v8si v8x;
	__attribute__ ((aligned(16))) static v8si v8y;
	__attribute__ ((aligned(16))) static v8si v8w;
	inline void _range(Node *u) {
		v8x = *(v8si *) (_dat[u-_nodes].px);
		v8y = *(v8si *) (_dat[u-_nodes].py);
		v8w = *(v8si *) (_dat[u-_nodes].val);
		v8ret += (qlx <= v8x) & (v8x <= qrx) & (qly <= v8y) & (v8y <= qry) & v8w;
	}
	void _range(Node *u, int k, int lx, int ly, int rx, int ry) {
		_range(u);
		if (qlx <= lx && rx <= qrx && qly <= ly && ry <= qry) {
			qret += sum[u-_nodes];
			return ;
		}
		if (lx > qrx || rx < qlx || ly > qry || ry < qly)
			return ;
		if (!k) {
			if (u->lson)
				_range(u->lson, !k, lx, ly, _dat[u-_nodes].px[0], ry);
			if (u->rson)
				_range(u->rson, !k, _dat[u-_nodes].px[0]+1, ly, rx, ry);
		} else {
			if (u->lson)
				_range(u->lson, !k, lx, ly, rx, _dat[u-_nodes].py[0]);
			if (u->rson)
				_range(u->rson, !k, lx, _dat[u-_nodes].py[0]+1, rx, ry);
		}
	}
	int range(int i, int d) {
		int x = A[i].xy[0], y = A[i].xy[1];
		qlx = x-d, qrx = x+d;
		qly = y-d, qry = y+d;
		qret = 0;
		memset(&v8ret, 0, sizeof(v8ret));
		_range(root, 0, lx, ly, rx, ry);
		qret += v8ret[0] + v8ret[1] + v8ret[2] + v8ret[3];
		return qret;
	}
} tree;
int KdTree::qlx, KdTree::qly, KdTree::qrx, KdTree::qry, KdTree::qret;
v8si KdTree::v8ret, KdTree::v8x, KdTree::v8y, KdTree::v8w;
struct Que {
	static int SQRTN;
	int l, r, id;
	Que(int l=0, int r=0, int id=0):
		l(l), r(r), id(id) {}
	bool operator<(const Que &q) const {
		if (l / SQRTN != q.l / SQRTN)
			return l / SQRTN < q.l / SQRTN;
		if ((l/SQRTN)&1)
			return r < q.r;
		else
			return r > q.r;
	}
} que[MAXQ];
int Que::SQRTN = 1;
void mo(int n, int d, int q, int ret[]) {
	Que::SQRTN = ceil(sqrt(n));
	sort(que, que+q);
	int l = 0, r = -1;
	int pcnt = 0;
	for (int i = 0; i < q; i++) {
		while (r < que[i].r)
			r++, pcnt += tree.range(r, d), tree.inc(r);
		while (r > que[i].r)
			tree.dec(r), pcnt -= tree.range(r, d), r--;
		while (l > que[i].l)
			l--, pcnt += tree.range(l, d), tree.inc(l);
		while (l < que[i].l)
			tree.dec(l), pcnt -= tree.range(l, d), l++;
		ret[que[i].id] = pcnt;
	}
}
int main() {
	int cases = 0;
	int n, d, q;
	int ret[MAXQ];
	while (scanf("%d %d %d", &n, &d, &q) == 3) {
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			tree.A[i] = Pt(x+y, x-y, i);	// rotate 45 degree
		}
		for (int i = 0; i < q; i++) {
			int l, r;
			scanf("%d %d", &l, &r);
			l--, r--;
			que[i] = Que(l, r, i);
		}

		tree.build(n);
		mo(n, d, q, ret);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}
/*
5 1 2
0 0
1 0
3 0
2 1
2 0

2 4
1 5

5 2 2
0 0
1 0
3 0
2 1
2 0

2 4
1 5
*/

