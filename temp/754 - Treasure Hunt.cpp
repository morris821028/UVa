#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#define eps 1e-8
#define MAXM 32767
struct Pt {
    double x, y;
    int label;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	bool operator==(const Pt &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
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
struct Seg {
	Pt s, e;
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {
		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
	double interpolate(double x) const {
		Pt p1 = s, p2 = e;
		if (p1.x == p2.x) return p1.y;
		return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
	}
};
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
int intersection(Pt a, Pt b, Pt c, Pt d) { // seg(a, b) and seg(c, d)
	return cmpZero(cross(a, c, b)) * cmpZero(cross(a, b, d)) > 0
		&& cmpZero(cross(c, a, d)) * cmpZero(cross(c, d, b)) > 0;
}
#define MAXH 100.0f
#define MAXW 100.0f
int validPos(double x, double y) {
	return 0 <= x && x <= MAXH
		&& 0 <= y && y <= MAXW;	
}
struct CMP {
	static double x;
	double interpolate(const Pt& p1, const Pt& p2, double& x) {
		if (p1.x == p2.x) return p1.y;
		return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
	}
	bool operator()(const Seg &i, const Seg &j) {
		double v1 = interpolate(i.s, i.e, x), v2 = interpolate(j.s, j.e, x);
		if (fabs(v1 - v2) > eps)
			return v1 < v2;
		return false;
	}
};
double CMP::x = 0;
class DisjointSet {
	public:
	int parent[MAXM];
	int findp(int x) {
		return parent[x] == x ? x : parent[x] = findp(parent[x]);
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if (x == y)	return 0;
		parent[x] = y;
		return 1;
	}
	void init(int n) {
		for (int i = 0; i <= n; i++)
			parent[i] = i;
	}
};

class PartitionMap {
	public:
	int n;
	DisjointSet disjointSet;
	Seg segs[1024];
	vector<double> X;
	vector<int> g[MAXM];
	set<Seg, CMP> tree[MAXM];
	vector<Pt> dual[MAXM];
	vector<Seg> dualLBound[MAXM], dualUBound[MAXM];
	vector<Pt> pts;
	void partition() {
		X.clear();
		for (int i = 0; i < n; i++) {
			X.push_back(segs[i].s.x);
			X.push_back(segs[i].e.x);
			for (int j = i+1; j < n; j++) {
				if (intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e)) {
					Pt p = getIntersect(segs[i], segs[j]);
					if (validPos(p.x, p.y)) {
						X.push_back(p.x);
					}
				}
			}
		}
		
		sort(X.begin(), X.end());
		int m = 1;
		for (int i = 1; i < X.size(); i++) {
			if (fabs(X[i] - X[m - 1]) > eps)
				X[m++] = X[i];
		}		
		X.resize(m);
		for (int i = 0; i < m; i++)
			tree[i].clear();
	}
	void buildMap() {
		int m = X.size();
		int region = 0;
		for (int i = 0; i < m; i++) {
			dual[i].clear();
			dualLBound[i].clear();
			dualUBound[i].clear();
		}
		pts.clear();
		for (int i = 0; i < m - 1; i++) {
			double mid = (X[i] + X[i+1])/2;
			CMP::x = mid;
			for (int j = 0; j < n; j++) {
				double sx = segs[j].s.x, ex = segs[j].e.x;
				if (sx <= X[i] && X[i+1] <= ex) {
					tree[i].insert(segs[j]);
				}
			}
			set<Seg, CMP>::iterator it = tree[i].begin(), jt = it;
			jt++;
			for (; it != tree[i].end() && jt != tree[i].end(); it++, jt++) {
				double a = (*it).interpolate(mid);
				double b = (*jt).interpolate(mid);
				double c = (a + b) /2.0;
				Pt p(mid, c);
				p.label = region++;
				dual[i].push_back(p);
				dualLBound[i].push_back(*it);
				dualUBound[i].push_back(*jt);
				pts.push_back(p);
			}
		}
//		printf("region %d\n", region);
			
		disjointSet.init(region);
		
		vector<int> tmpg[MAXM];
		for (int i = 0; i < m; i++) {
			for (int j = 1; j < dual[i].size(); j++) {
				int x = dual[i][j].label;
				int y = dual[i][j-1].label;
				tmpg[x].push_back(y);
				tmpg[y].push_back(x);
			}
		}
		for (int i = 0; i < m - 2; i++) {
			for (int j = 0; j < dual[i].size(); j++) {
				for (int k = 0; k < dual[i+1].size(); k++) {
					double y1, y2, y3, y4;
					
					y1 = dualLBound[i][j].interpolate(X[i+1]);
					y2 = dualUBound[i][j].interpolate(X[i+1]);
					y3 = dualLBound[i+1][k].interpolate(X[i+1]);
					y4 = dualUBound[i+1][k].interpolate(X[i+1]);

					if (max(y1, y3) < min(y2, y4)) {					
//						printf("%lf %lf, %lf %lf\n", y1, y2, y3, y4);
//						getchar();
						Pt p(X[i+1], (max(y1, y3) + min(y2, y4))/2);
						int ok = 1;
						for (int t = 0; t < n && ok; t++) {
							if (onSeg(segs[t].s, segs[t].e, p))
								ok = 0;
						}
						if (ok)
							disjointSet.joint(dual[i][j].label, dual[i+1][k].label);
						else {
							tmpg[dual[i][j].label].push_back(dual[i+1][k].label);
							tmpg[dual[i+1][k].label].push_back(dual[i][j].label);
						}
					}
				}
			}
		}
		
		for (int i = 0; i < region; i++)
			g[i].clear();
		for (int i = 0; i < region; i++) {
			int x = disjointSet.findp(i);
			for (int j = 0; j < tmpg[i].size(); j++) {
				int y = disjointSet.findp(tmpg[i][j]);
				g[x].push_back(y);
			}
		}
		
		int diff = 0;
		for (int i = 0; i < region; i++) {
			sort(g[i].begin(), g[i].end());
			g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
			if (g[i].size())
				diff++;
		}
//		printf("diffffffff %d\n", diff);
	}
	
	int findLocation(Pt p) {
		set<Seg>::iterator it, jt;
		for (int i = 0; i < X.size() - 1; i++) {
			if (X[i] <= p.x && p.x <= X[i+1]) {
				double mid = (X[i] + X[i+1])/2;
				CMP::x = mid;
				it = tree[i].lower_bound(Seg(p, p));
				jt = it, jt--;
				double a = (*it).interpolate(mid);
				double b = (*jt).interpolate(mid);
				double c = (a + b) /2.0;
				for (int j = 0; j < dual[i].size(); j++) {
					if (dual[i][j] == Pt(mid, c))
						return disjointSet.findp(dual[i][j].label);
				}
			}
		}
		return -1;
	}
	int path(Pt p, Pt q) {
		int st = findLocation(p);
		int ed = findLocation(q);
		map<int, int> dist;
		queue<int> Q;
		Q.push(st), dist[st] = 0;
//		printf("st %d ed %d\n", st, ed);
		while (!Q.empty()) {
			int u = Q.front(), d = dist[u] + 1;
			Q.pop();
//			printf("%d %lf %lf, dist %d\n", u, pts[u].x, pts[u].y, d);
			if (u == ed)	return d - 1;
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i];
				if (dist.count(v))	continue;
				dist[v] = d, Q.push(v);
//				printf("%d -> %d\n", u, v);
			}
		}
		return -1;
	}
	
	void init(Seg A[], int n) {
		for (int i = 0; i < n; i++)
			this->segs[i] = A[i];
		this->n = n;
		
		for (int i = 0; i < n; i++) {
			if (segs[i].e < segs[i].s)
				swap(segs[i].s, segs[i].e);
		}
		
		partition();
		buildMap();		
	}
} mMap;
int main() {
	int testcase, n;
	double sx, sy, ex, ey;
	Seg segs[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
			segs[i] = Seg(Pt(sx, sy), Pt(ex, ey));
		}
		
		// inter map
		segs[n] = Seg(Pt(0, 0), Pt(MAXH, 0)), n++;
		segs[n] = Seg(Pt(MAXH, 0), Pt(MAXH, MAXW)), n++;
		segs[n] = Seg(Pt(MAXH, MAXW), Pt(0, MAXW)), n++;
		segs[n] = Seg(Pt(0, MAXW), Pt(0, 0)), n++;
		
		// outer map
		int GAP = 10;
		segs[n] = Seg(Pt(-GAP, -GAP), Pt(MAXH + GAP, -GAP)), n++;
		segs[n] = Seg(Pt(MAXH + GAP, -GAP), Pt(MAXH + GAP, MAXW + GAP)), n++;
		segs[n] = Seg(Pt(MAXH + GAP, MAXW + GAP), Pt(-GAP, MAXW + GAP)), n++;
		segs[n] = Seg(Pt(-GAP, MAXW + GAP), Pt(-GAP, -GAP)), n++;
		
		mMap.init(segs, n);
		
		scanf("%lf %lf", &sx, &sy);
		int ret = mMap.path(Pt(sx, sy), Pt(-GAP/2, -GAP/2));
		printf("Number of doors = %d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2

7
20 0 37 100
40 0 76 100
85 0 0 75
100 90 0 90
0 71 100 61
0 14 100 38
100 47 47 100
54.5 55.4

7
20 0 37 100
40 0 76 100
85 0 0 75
100 90 0 90
0 71 100 61
0 14 100 38
100 47 47 100
1 1
*/
