#include <bits/stdc++.h>
using namespace std;

#define eps 1e-8
#define MAXN 1024
#define INF 1e+12
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
    std::size_t operator() (const Pt& _pt) const {
        return std::hash<double>()(_pt.x)^std::hash<double>()(_pt.y);
    }
};
struct Seg {
    Pt s, e;
    Seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
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
Pt intersection(Pt a, Pt b, Pt c, Pt d) { // seg(a, b) and seg(c, d)
	double c1 = cross2(d-c, a-c), c2 = cross2(d-c, b-c);
    if (cmpZero(c1) * cmpZero(c2) > 0)
    	return Pt(INF, INF);
    if (cmpZero(c1) == 0 && cmpZero(c2) == 0) {
    	double d1 = dot(d-c, a-c), d2 = dot(d-c, b-c);
    	if (d1 < 0 && d2 < 0)
    		return Pt(INF, INF);
    	if (d1 <= 0 && d2 <= 0)
    		return c;
    	d1 = dot(c-d, a-d), d2 = dot(c-d, b-d);
    	if (d1 < 0 && d2 < 0)
    		return Pt(INF, INF);
    	if (d1 <= 0 && d2 <= 0)
    		return d;
    	assert(false);
	}
	c1 = cross2(b-a, c-a), c2 = cross2(b-a, d-a);
	if (cmpZero(c1) * cmpZero(c2) > 0)
		return Pt(INF, INF);
	return getIntersect(Seg(a, b), Seg(c, d));
}
struct AngleCmp {
	Pt o;
	AngleCmp(Pt o = Pt()):o(o) {}
	bool operator() (const Pt& ppa, const Pt& ppb) {
		Pt pa = ppa, pb = ppb;
		Pt p1 = pa - o, p2 = pb - o;
	    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
	    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
	    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
	    if (p1.y * p2.y < 0) return p1.y > p2.y;
	    double c = cross2(p1, p2);
	    return c > 0 || (c == 0 && fabs(p1.x) < fabs(p2.x));
	}
};
int countTriangle(map<Pt, vector<Pt>> &g) {
	int ret = 0;
	for (auto &a : g) {
		const auto &adj = g[a.first];
		for (auto &b : adj) {
			const auto &adj2 = g[b];
			int idx2 = 0;
			for (; idx2 < adj2.size(); idx2++) {
				if (adj2[idx2] == a.first)
					break;
			}
			auto &c = adj2[(idx2+1)%adj2.size()];
			const auto &adj3 = g[c];
			int idx3 = 0;
			for (; idx3 < adj3.size(); idx3++) {
				if (adj3[idx3] == b)
					break;
			}
			auto &d = adj3[(idx3+1)%adj3.size()];
			if (a.first == d)
				ret++;
		}
	}
	return ret/3;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		scanf("%d", &n);
		vector<Seg> segs(n);
		for (int i = 0; i < n; i++) {
			int xa, xb, ya, yb;
			scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
			segs[i] = Seg(Pt(xa, ya), Pt(xb, yb));
		}

		set<Pt> S;
		for (int i = 0; i < n; i++)
			S.insert(segs[i].s), S.insert(segs[i].e);

		map<Pt, vector<Pt>> g;
		for (int i = 0; i < n; i++) {
			vector<Pt> a;
			a.push_back(segs[i].s);
			a.push_back(segs[i].e);
			for (int j = 0; j < n; j++) {
				if (i == j)	continue;
				Pt p = intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e);
				if (p.x != INF)
					a.push_back(p);
			}
			sort(a.begin(), a.end());
			a.resize(unique(a.begin(), a.end()) - a.begin());
			auto *prev = &g[a[0]];
			for (int j = 1; j < a.size(); j++) {
				prev->push_back(a[j]);
				prev = &g[a[j]];
				prev->push_back(a[j-1]);
			}
		}

		for (auto &e : g)
			sort(e.second.begin(), e.second.end(), AngleCmp(e.first));
		int ret = countTriangle(g);
		printf("Case %d:\n", ++cases);
		printf("%d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
3
3
-1 0 3 0
0 -1 0 3
-1 3 3 -1
4
-3 0 3 0
-3 -1 1 3
3 -1 -1 3
0 3 0 -1
6
-3 -2 3 -2
-2 -3 -2 3
-3 2 3 2
2 -3 2 3
-3 -3 3 3
1 -1 -1 1
*/
