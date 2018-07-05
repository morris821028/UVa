#include <bits/stdc++.h> 
using namespace std;

const double eps = 1e-8;
const double BOX_MX = (3000000);
const int AUXID = 200000;

struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0): x(a), y(b) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y); }
    Pt operator*(const double a) const { return Pt(x * a, y * a);  }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    void println() const {
    	printf("(%lf, %lf)\n", x, y);
	}
};


struct Seg {
    Pt s, e;
	int i;
    Seg() {}
    Seg(Pt a, Pt b, int i):s(a), e(b), i(i) {}
    void println() {
    	printf("Segment((%lf, %lf), (%lf, %lf))\n", s.x, s.y, e.x, e.y);
	}
};
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}

struct AngleCmp {
	Pt o;
	AngleCmp(Pt o = Pt()):o(o) {}
	bool operator() (const pair<Pt, int>& ppa, const pair<Pt, int>& ppb) {
		Pt pa = ppa.first, pb = ppb.first;
		Pt p1 = pa - o, p2 = pb - o;
	    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
	    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
	    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
	    if (p1.y * p2.y < 0) return p1.y > p2.y;
	    double c = cross2(p1, p2);
	    return c > 0 || (c == 0 && fabs(p1.x) < fabs(p2.x));
	}
};


static Pt pts[10005];
static Seg segs[30005];

struct BSP {
	struct Node {
		double lx, ly, rx, ry;
		Node *ls, *ms, *rs;
		int sn;
		Seg *seg;
		void extend(Node *u) {
			if (u == NULL)
				return ;
			lx = min(lx, u->lx), ly = min(ly, u->ly);
			rx = max(rx, u->rx), ry = max(ry, u->ry);
		}
	} nodes[262144];
	Seg segs[262144];
	Node *root;
	int size;
	Node* newNode() {
		Node *p = &nodes[size++];
		assert(size < 262144);
		p->ls = p->ms = p->rs = NULL;
		p->sn = 0;
		return p;
	}
	Node* _build(Seg segs[], int n) {
		if (n == 0)
			return NULL;
			
		double box_lx = BOX_MX, box_ly = BOX_MX;
		double box_rx = -BOX_MX, box_ry = -BOX_MX;
		for (int i = 0; i < n; i++) {
			box_rx = max(box_rx, max(segs[i].s.x, segs[i].e.x));
			box_ry = max(box_ry, max(segs[i].s.y, segs[i].e.y));
			box_lx = min(box_lx, min(segs[i].s.x, segs[i].e.x));
			box_ly = min(box_ly, min(segs[i].s.y, segs[i].e.y));
		}
		
		const int m = n/2;
		int Lsize = 0, Msize = 0, Rsize = 0;
		Seg *L = NULL, *M = NULL, *R = NULL;
		if (box_rx - box_lx > box_ry - box_ly) {
			const double mval = (box_rx + box_lx)/2;
			L = segs;
			R = std::partition(segs, segs+n, [mval](const Seg &s) {
            	return max(s.s.x, s.e.x) < mval;
        	});
        	M = std::partition(R, segs+n, [mval](const Seg &s) {
            	return min(s.s.x, s.e.x) < mval;
        	});
        	Msize = segs+n - M;
        	Rsize = M - R;
        	Lsize = R - segs;
		} else {
			const double mval = (box_ry + box_ly)/2;
			L = segs;
			R = std::partition(segs, segs+n, [mval](const Seg &s) {
            	return max(s.s.y, s.e.y) < mval;
        	});
        	M = std::partition(R, segs+n, [mval](const Seg &s) {
            	return min(s.s.y, s.e.y) < mval;
        	});
        	Msize = segs+n - M;
        	Rsize = M - R;
        	Lsize = R - segs;
		}
		
		Node *u = newNode();
		if (Lsize == n || Rsize == n || Msize == n) {
			u->sn = n, u->seg = segs;
		} else {
			u->ls = _build(L, Lsize);
			u->rs = _build(R, Rsize);
			u->ms = _build(M, Msize);
		}
		
		u->lx = BOX_MX, u->ly = BOX_MX; 
		u->rx = -BOX_MX, u->ry = -BOX_MX;
		for (int i = 0; i < u->sn; i++) {
			u->lx = min(u->lx, min(u->seg[i].s.x, u->seg[i].e.x));
			u->ly = min(u->ly, min(u->seg[i].s.y, u->seg[i].e.y));
			u->rx = max(u->rx, max(u->seg[i].s.x, u->seg[i].e.x));
			u->ry = max(u->ry, max(u->seg[i].s.y, u->seg[i].e.y));
		}
		
		u->extend(u->ls);
		u->extend(u->rs);
		u->extend(u->ms);
		return u;
	}
	void build_tree(Seg segs[], int m) {
		memcpy(this->segs, segs, sizeof(segs[0])*m);
		size = 0;
		root = _build(this->segs, m);
	}
	
	Pt q_st, q_ed;
	int q_si;
	
	void rayhit(Seg &seg) {
		if (seg.s.x == seg.e.x) {
			if (cmpZero(seg.s.x - q_st.x) == 0) {
				double low = min(seg.s.y, seg.e.y);
				if (low > q_st.y && low < q_ed.y) {
					q_ed.y = low;
					q_si = seg.i;
				}
			}
			return ;
		}
		
		if (max(seg.s.x, seg.e.x) < q_st.x || min(seg.s.x, seg.e.x) > q_st.x)
			return ;
		double y = seg.s.y + (double) (seg.e.y - seg.s.y) / (seg.e.x - seg.s.x) * (q_st.x - seg.s.x);
		if (y > q_st.y && y < q_ed.y) {
			q_ed.y = y;
			q_si = seg.i;
		}
	}
	void search(Node *u) {
		if (u == NULL)
			return ;
		if (u->lx > q_st.x || u->rx < q_st.x || u->ry < q_st.y || u->ly > q_ed.y)
			return ;
		for (int i = 0; i < u->sn; i++)
			rayhit(u->seg[i]);
		search(u->ls);
		search(u->ms);
		search(u->rs);
	}
	pair<int, Pt> raycast(Pt st) {
		q_st = st; 
		q_ed = Pt(st.x, BOX_MX+1);
		q_si = -1;
		search(root);
		return {q_si, q_ed};
	}
} tree;

static int parent[1048576], weight[1048576];
void init(int n) {
	if (n >= 1048576)
		exit(0);
	for (int i = 0; i <= n; i++)
		parent[i] = i, weight[i] = 1;
}
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (weight[x] > weight[y])
		parent[y] = x, weight[x] += weight[y];
	else
		parent[x] = y, weight[y] += weight[x];
}

int main() {
	int n, m, p, q;
	while (scanf("%d %d %d %d", &n, &m, &p, &q) == 4 && n) {
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pts[i] = Pt(x, y);
		}
		
		for (int i = 0; i < m; i++) {
			int st_i, ed_i;
			scanf("%d %d", &st_i, &ed_i);
			st_i--, ed_i--;
			segs[i] = Seg(pts[st_i], pts[ed_i], i);
		}
		
		segs[m] = Seg(Pt(BOX_MX, BOX_MX), Pt(BOX_MX, -BOX_MX), m), m++;
		segs[m] = Seg(Pt(BOX_MX, -BOX_MX), Pt(-BOX_MX, -BOX_MX), m), m++;
		segs[m] = Seg(Pt(-BOX_MX, -BOX_MX), Pt(-BOX_MX, BOX_MX), m), m++;
		segs[m] = Seg(Pt(-BOX_MX, BOX_MX), Pt(BOX_MX, BOX_MX), m), m++;
		
		map<Pt, vector<pair<Pt, int>>> g;
		vector<vector<Pt>> on_seg(m);
		
		for (int i = 0; i < m; i++) {
			on_seg[segs[i].i].push_back(segs[i].s);
			on_seg[segs[i].i].push_back(segs[i].e);
		}
		
//		for (int i = 0; i < n; i++)
//			pts[i].println();
//		for (int i = 0; i < m; i++)
//			segs[i].println();

		tree.build_tree(segs, m);
		{
			vector<Pt> q;
			for (int i = 0; i < m-4; i++) {
				pair<int, Pt> hit;
				if (segs[i].s.x == segs[i].e.x) {
					int x = segs[i].s.x, y = max(segs[i].s.y, segs[i].e.y);
					q.push_back(Pt(x, y));
				} else {
					q.push_back(segs[i].s);
					q.push_back(segs[i].e);
				}
			}
			sort(q.begin(), q.end());
			q.resize(unique(q.begin(), q.end()) - q.begin());
			for (auto p : q) {
				auto hit = tree.raycast(p);
				if (hit.first >= 0) {
					on_seg[hit.first].push_back(hit.second);
					g[p].push_back({hit.second, AUXID});
					g[hit.second].push_back({p, AUXID});
				}
			}
		}
		
		for (int i = 0; i < p; i++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			pair<int, Pt> hit = tree.raycast(Pt(x, y));
			if (hit.first >= 0) {
				on_seg[hit.first].push_back(hit.second);
				g[Pt(x, y)].push_back({hit.second, i+1});
				g[hit.second].push_back({Pt(x, y), i+1});
			}
		}
		
		for (int i = 0; i < q; i++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			pair<int, Pt> hit = tree.raycast(Pt(x, y));
			if (hit.first >= 0) {
				on_seg[hit.first].push_back(hit.second);
				g[Pt(x, y)].push_back({hit.second, -(i+1)});
				g[hit.second].push_back({Pt(x, y), -(i+1)});
			}
		}
		
		for (int i = 0; i < m; i++) {
			vector<Pt> &a = on_seg[i];
			sort(a.begin(), a.end());
			a.resize(unique(a.begin(), a.end()) - a.begin());
			auto *prev = &g[a[0]];
			for (int j = 1; j < a.size(); j++) {
				prev->push_back({a[j], 0});
				prev = &g[a[j]];
				prev->push_back({a[j-1], 0});
			}
		}
		
		for (auto &e : g) {
			sort(e.second.begin(), e.second.end(), AngleCmp(e.first));
			if (e.second.size() == 0)
				continue;
			int n = 0, hasUp = 0, hasDown = 0;
			for (int i = 0; i < e.second.size(); i++) {
				if (cmpZero(e.second[i].first.x - e.first.x) == 0 && e.second[i].second == 0) {
					if (e.second[i].first.y > e.first.y)
						hasUp = 1;
					if (e.second[i].first.y < e.first.y)
						hasDown = 1;
				}				
			}
			for (int i = 0; i < e.second.size(); i++) {
				if (i != 0 && e.second[i] == e.second[i-1])
					continue;
				if (e.second[i].second != AUXID ||
					(e.second[i].first.y > e.first.y && hasUp == 0) ||
					(e.second[i].first.y < e.first.y && hasDown == 0))
					e.second[n] = e.second[i], n++;
			}
			e.second.resize(n);
		}
		
		map<pair<Pt, Pt>, int> R;
		for (auto &e : g) {
			int sz = e.second.size();
			for (int i = 0; i < sz; i++) {
				if (R.find(make_pair(e.first, e.second[i].first)) == R.end()) {
					int eid = R.size()+1;
					R[{e.first, e.second[i].first}] = eid;
				}
			}
		}
		
		init(R.size());
		for (auto &e : g) {
			int sz = e.second.size();
			for (int i = sz-1, j = 0; j < sz; i = j++) {
				int l = R[{e.second[i].first, e.first}];
				int r = R[{e.first, e.second[j].first}];
				joint(l, r);
				if (e.second[i].second != 0) {
					r = R[{e.first, e.second[i].first}];
					assert(l > 0 && r > 0);
					joint(l, r);
				}
			}
		}
		
		vector<int> region(R.size()+1, 0);
		for (auto &e : g) {
			int sz = e.second.size();
			for (int i = 0; i < sz; i++) {
				if (e.second[i].second > 0 && e.second[i].second != AUXID) {
					int l = R[{e.second[i].first, e.first}];
					l = findp(l);
					region[l] = e.second[i].second;
				}
			}
		}

		static int ret[100005];
		memset(ret, 0, sizeof(ret));
		
		for (auto &e : g) {
			int sz = e.second.size();
			for (int i = 0; i < sz; i++) {
				if (e.second[i].second < 0 && ret[-e.second[i].second] == 0) {
					int l = R[{e.second[i].first, e.first}];
					l = findp(l);
					if (region[l])
						ret[-e.second[i].second] = region[l];
				}
			}
		}
			
		for (int i = 1; i <= q; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}
