#include <bits/stdc++.h> 
using namespace std;

const float eps = 1e-6;
const float BOX_MX = 2000000;

struct Pt {
    float x, y;
    Pt() {}
    Pt(float a, float b): x(a), y(b) {}
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
int cmpZero(float v) {
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
	static const int MAXN = 60005;
	static const int MAXNODE = 60005;
	struct Node {
		float lx, ly, rx, ry;
		Node *ls, *ms, *rs;
		void extend(Node *u) {
			if (u == NULL)
				return ;
			lx = min(lx, u->lx), ly = min(ly, u->ly);
			rx = max(rx, u->rx), ry = max(ry, u->ry);
		}
	} nodes[MAXNODE];
	int sn[MAXNODE];
	Seg *seg[MAXNODE];
	float axis[MAXN];
	Node *root;
	int size;
	Node* newNode() {
		Node *p = &nodes[size++];
		assert(size < MAXNODE);
		p->ls = p->ms = p->rs = NULL;
		sn[p-nodes] = 0;
		return p;
	}
	Node* _build(int k, Seg segs[], int n) {
		if (n == 0)
			return NULL;
		if (k == 2)
			k = 0;

		int Lsize = 0, Msize = 0, Rsize = 0;
		Seg *L = NULL, *M = NULL, *R = NULL;
		if (k == 0) {
			for (int i = 0; i < n; i++)
				axis[i<<1] = segs[i].s.x, axis[i<<1|1] = segs[i].e.x;
			nth_element(axis, axis+n, axis+2*n);
			const float mval = axis[n];
			L = segs;
			R = std::partition(segs, segs+n, [mval](const Seg &s) {
            	return max(s.s.x, s.e.x) <= mval;
        	});
        	M = std::partition(R, segs+n, [mval](const Seg &s) {
            	return min(s.s.x, s.e.x) <= mval;
        	});
        	Msize = segs+n - M;
        	Rsize = M - R;
        	Lsize = R - segs;
		} else {
			for (int i = 0; i < n; i++)
				axis[i<<1] = segs[i].s.y, axis[i<<1|1] = segs[i].e.y;
			nth_element(axis, axis+n, axis+2*n);
			const float mval = axis[n];
			L = segs;
			R = std::partition(segs, segs+n, [mval](const Seg &s) {
            	return max(s.s.y, s.e.y) <= mval;
        	});
        	M = std::partition(R, segs+n, [mval](const Seg &s) {
            	return min(s.s.y, s.e.y) <= mval;
        	});
        	Msize = segs+n - M;
        	Rsize = M - R;
        	Lsize = R - segs;
		}
		
		Node *u = newNode();
		u->lx = BOX_MX, u->ly = BOX_MX; 
		u->rx = -BOX_MX, u->ry = -BOX_MX;
		if (Lsize == n || Rsize == n || Msize == n) {
			sn[u - nodes] = n, seg[u - nodes] = segs;
			for (int i = 0; i < n; i++) {
				u->lx = min(u->lx, min(segs[i].s.x, segs[i].e.x));
				u->rx = max(u->rx, max(segs[i].s.x, segs[i].e.x));
				u->ly = min(u->ly, min(segs[i].s.y, segs[i].e.y));
				u->ry = max(u->ry, max(segs[i].s.y, segs[i].e.y));
			}
		} else {
			u->ls = _build(k+1, L, Lsize), u->extend(u->ls);
			u->ms = _build(k+1, M, Msize), u->extend(u->ms);
			u->rs = _build(k+1, R, Rsize), u->extend(u->rs);
		}		
		return u;
	}
	void build_tree(Seg s[], int m) {
		size = 0;
		root = _build(0, s, m);
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
		float y = seg.s.y + (float) (seg.e.y - seg.s.y) * (q_st.x - seg.s.x) / (seg.e.x - seg.s.x);
		if (y > q_st.y && y < q_ed.y) {
			q_ed.y = y;
			q_si = seg.i;
		}
	}
	void search(Node *u) {
		if (u == NULL)
			return ;
		if (u->lx > q_st.x || u->rx < q_st.x || u->ry <= q_st.y || u->ly >= q_ed.y)
			return ;
		for (int i = 0; i < sn[u - nodes]; i++)
			rayhit(seg[u - nodes][i]);
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

struct Disjoint {
	static const int MAXN = 65536;
	uint16_t parent[MAXN], weight[MAXN];
	void init(int n) {
		if (n >= MAXN)
			exit(0);
		for (int i = 0; i <= n; i++)
			parent[i] = i, weight[i] = 1;
	}
	int findp(int x) {
		return parent[x] == x ? x : parent[x] = findp(parent[x]);
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if (weight[x] >= weight[y])
			parent[y] = x, weight[x] += weight[y];
		else
			parent[x] = y, weight[y] += weight[x];
	}	
} egroup, sgroup;

int main() {
	int n, m, p, q;
	while (scanf("%d %d %d %d", &n, &m, &p, &q) == 4 && n) {
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pts[i] = Pt(x, y);
		}
		
		sgroup.init(n);
		for (int i = 0; i < m; i++) {
			int st_i, ed_i;
			scanf("%d %d", &st_i, &ed_i);
			st_i--, ed_i--;
			segs[i] = Seg(pts[st_i], pts[ed_i], i);
			sgroup.joint(st_i, ed_i);
		}
		
		segs[m] = Seg(Pt(BOX_MX, BOX_MX), Pt(BOX_MX, -BOX_MX), m), m++;
		segs[m] = Seg(Pt(BOX_MX, -BOX_MX), Pt(-BOX_MX, -BOX_MX), m), m++;
		segs[m] = Seg(Pt(-BOX_MX, -BOX_MX), Pt(-BOX_MX, BOX_MX), m), m++;
		segs[m] = Seg(Pt(-BOX_MX, BOX_MX), Pt(BOX_MX, BOX_MX), m), m++;
		
		static map<Pt, vector<pair<Pt, uint8_t>>> g; g.clear();
		static vector<vector<Pt>> on_seg; on_seg.clear(); on_seg.resize(m);
		
		for (int i = 0; i < m; i++) {
			on_seg[segs[i].i].reserve(4);
			on_seg[segs[i].i].push_back(segs[i].s);
			on_seg[segs[i].i].push_back(segs[i].e);
		}
		
//		for (int i = 0; i < n; i++)
//			pts[i].println();
//		for (int i = 0; i < m; i++)
//			segs[i].println();

		tree.build_tree(segs, m);
		{
			Pt top[10005];
			for (int i = 0; i < n; i++)
				top[i] = pts[i];
			for (int i = 0; i < n; i++) {
				int gid = sgroup.findp(i);
				if (top[gid].y < pts[i].y)
					top[gid] = pts[i];
			}
			
			for (int i = 0; i < n; i++) {
				if (sgroup.findp(i) != i)
					continue;
				auto p = top[i];
				auto hit = tree.raycast(p);
				if (hit.first >= 0) {
					on_seg[hit.first].emplace_back(hit.second);
					g[p].emplace_back(hit.second, 1);
					g[hit.second].emplace_back(p, 1);
				}
			}
		}
		
		for (int i = 0; i < m; i++) {
			vector<Pt> &a = on_seg[i];
			sort(a.begin(), a.end());
			a.resize(unique(a.begin(), a.end()) - a.begin());
			auto *prev = &g[a[0]];
			for (int j = 1; j < a.size(); j++) {
				prev->emplace_back(a[j], 0);
				prev = &g[a[j]];
				prev->emplace_back(a[j-1], 0);
			}
		}
		
		for (auto &e : g)
			sort(e.second.begin(), e.second.end(), AngleCmp(e.first));
		
		static map<Pt, map<Pt, int>> R; R.clear();
		int Rsize = 0;
		for (auto &e : g) {
			int sz = e.second.size();
			map<Pt, int> &Rg = R[e.first];
			for (auto &f : e.second) {
				int &eid = Rg[f.first];
				if (eid == 0)
					eid = ++Rsize;
			}
		}
		
		egroup.init(Rsize);
		for (auto &e : g) {
			int sz = e.second.size();
			map<Pt, int> &Rg = R[e.first];
			for (int i = sz-1, j = 0; j < sz; i = j++) {
				int l = R[e.second[i].first][e.first];
				int r = Rg[e.second[j].first];
				egroup.joint(l, r);
				if (e.second[i].second != 0) {
					r = Rg[e.second[i].first];
					assert(l > 0 && r > 0);
					egroup.joint(l, r);
				}
			}
		}
		
		for (auto &e : g) {
			int sz = e.second.size();
			int n = 0;
			for (int i = 0; i < sz; i++) {
				if (e.second[i].second == 0)
					e.second[n++] = e.second[i];
			}
			e.second.resize(n);
		}
		
		static int region[65536]; memset(region, 0, sizeof(0)*Rsize);
		
		for (int i = 0; i < p; i++) {
			float x, y;
			scanf("%f %f", &x, &y);
			pair<int, Pt> hit = tree.raycast(Pt(x, y));
			if (hit.first < 0)
				continue;
				
			if (g.find(hit.second) != g.end()) {
				auto &adj = g[hit.second];
				AngleCmp cmp(hit.second);
				int pos = 0;
				pair<Pt, int> q(Pt(x, y), i+1);
				pos = lower_bound(adj.begin(), adj.end(), q, cmp) - adj.begin() - 1;
				assert(pos >= 0);
				int l = R[adj[pos].first][hit.second];
				assert(l > 0);
				l = egroup.findp(l);
				region[l] = i+1;
			} else {
				auto &adj = on_seg[hit.first];
				Pt lpt = adj[0], rpt = adj[1];
				int l;
				if (cmpZero(cross(lpt, rpt, Pt(x, y))) <= 0)
					l = R[lpt][rpt];
				else
					l = R[rpt][lpt];
				assert(l > 0);
				l = egroup.findp(l);
				region[l] = i+1;
			}
		}
		
		for (int i = 0; i < q; i++) {
			float x, y;
			scanf("%f %f", &x, &y);
			pair<int, Pt> hit = tree.raycast(Pt(x, y));
			if (hit.first < 0) {
				printf("0\n");
				continue;
			}
				
			if (g.find(hit.second) != g.end()) {
				auto &adj = g[hit.second];
				AngleCmp cmp(hit.second);
				int pos = 0;
				pair<Pt, int> q(Pt(x, y), i+1);
				pos = lower_bound(adj.begin(), adj.end(), q, cmp) - adj.begin() - 1;
				assert(pos >= 0);
				int l = R[adj[pos].first][hit.second];
				assert(l > 0);
				l = egroup.findp(l);
				printf("%d\n", region[l]);
			} else {
				auto &adj = on_seg[hit.first];
				Pt lpt = adj[0], rpt = adj[1];
				int l;
				if (cmpZero(cross(lpt, rpt, Pt(x, y))) <= 0)
					l = R[lpt][rpt];
				else
					l = R[rpt][lpt];
				assert(l > 0);
				l = egroup.findp(l);
				printf("%d\n", region[l]);
			}
		}
	}
	return 0;
}
