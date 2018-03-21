#include <bits/stdc++.h>
using namespace std;
// mo's algorithm, kd tree
struct Pt {
	int xy[2], id;
	Pt(int x=0, int y=0, int id=0):
		id(id) {xy[0] = x, xy[1] = y;}
};
struct sPt {
	int xy[2];
	sPt(int x=0, int y=0) {xy[0] = x, xy[1] = y;}
};

const int MAXN = 200005;
const int MAXQ = 1005;
struct KdTree {
	struct Node {
		Node *lson, *rson, *p;
		sPt pid;
		int sum, val;
	} _nodes[MAXN], *root, *loc[MAXN];
	int nodeIdx;
	Pt A[MAXN];
	int lx, ly, rx, ry;
	static int sortIdx;
	static bool cmp(const Pt &x, const Pt &y) {
		return x.xy[sortIdx] < y.xy[sortIdx];
	}
	Node* _build(int k, int l, int r, Node *p) {
		if (l > r)
			return NULL;
		int m = (l+r)>>1;
		Node *ret = &_nodes[nodeIdx++];
		sortIdx = k;
		nth_element(A+l, A+m, A+r+1, cmp);
		while (m < r && A[m].xy[sortIdx] == A[m+1].xy[sortIdx])
			m++;
		ret->p = p;
		ret->pid = sPt(A[m].xy[0], A[m].xy[1]);
		ret->sum = ret->val = 0;
		ret->lson = _build(!k, l, m-1, ret);
		ret->rson = _build(!k, m+1, r, ret);
		loc[A[m].id] = ret;
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
	}
	void inc(int i) {
		Node *p = loc[i];
		p->val++;
		while (p != NULL)
			p->sum++, p = p->p;
	}
	void dec(int i) {
		Node *p = loc[i];
		p->val--;
		while (p != NULL)
			p->sum--, p = p->p;
	}
	static int qlx, qly, qrx, qry, qret;
	void _range(Node *u, int k, int lx, int ly, int rx, int ry) {
		if (lx > qrx || rx < qlx || ly > qry || ry < qly || u->sum == 0)
			return ;
		if (qlx <= lx && rx <= qrx && qly <= ly && ry <= qry) {
			qret += u->sum;
			return ;
		}
		if (qlx <= u->pid.xy[0] && u->pid.xy[0] <= qrx && qly <= u->pid.xy[1] && u->pid.xy[1] <= qry)
			qret += u->val;
		if (!k) {
			if (u->lson)
				_range(u->lson, !k, lx, ly, u->pid.xy[0], ry);
			if (u->rson)
				_range(u->rson, !k, u->pid.xy[0]+1, ly, rx, ry);
		} else {
			if (u->lson)
				_range(u->lson, !k, lx, ly, rx, u->pid.xy[1]);
			if (u->rson)
				_range(u->rson, !k, lx, u->pid.xy[1]+1, rx, ry);
		}
	}
	int range(int i, int d) {
		sPt p = loc[i]->pid;
		qlx = p.xy[0]-d, qrx = p.xy[0]+d;
		qly = p.xy[1]-d, qry = p.xy[1]+d;
		qret = 0;
		_range(root, 0, lx, ly, rx, ry);
		return qret;
	}
} tree;
int KdTree::sortIdx = 0;
int KdTree::qlx, KdTree::qly, KdTree::qrx, KdTree::qry, KdTree::qret;
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
