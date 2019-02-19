#include <bits/stdc++.h>
using namespace std;

#include <ext/rope>
using namespace __gnu_cxx;

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

class Rope {
public:
	rope<int> r;
	void init() {
		r.clear();
	}
	int next(rope<int>::const_iterator it) {
		it++;
		if (it == r.end())
			return *r.begin();
		return *it;
	}
	int prev(rope<int>::const_iterator it) {
		if (it == r.begin())
			return *r.rbegin();
		it--;
		return *it;
	}
	tuple<int, int, int> insert(int data, int pos) {
		r.insert(pos, data);
		auto it = r.begin() + pos;
		int p = prev(it);
		int q = next(it);
		return make_tuple(p, data, q);
	}
	tuple<int, int, int> remove(int pos) {
		auto it = r.begin() + pos;
		int del = *it;
		int p = prev(it);
		int q = next(it);
		r.erase(pos, 1);
		return make_tuple(p, del, q);
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
		if (l == r)
			return ret;
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
		if (l == r)
			return;
		int m = (l+r)/2;
		if (s.first.q.x <= mesh.X[m])			insert(u->lson, l, m, s);
		else if (s.first.p.x >= mesh.X[m])	insert(u->rson, m, r, s);
		else	insert(u->lson, l, m, s), insert(u->rson, m, r, s);
	}
	void remove(Node* &u, int l, int r, pair<PtP, int> s) {
		if (u == NULL)
			return;
		if (s.first.p.x <= mesh.X[l] && mesh.X[r] <= s.first.q.x) {
			PtP::x = (mesh.X[l] + mesh.X[r])/2.0;
			u->segs.erase(s);
			return;
		}
		if (l == r)
			return;
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
