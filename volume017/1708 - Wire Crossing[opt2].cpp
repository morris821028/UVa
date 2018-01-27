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

int bfs(map<Pt, vector<pair<Pt, int>>> &g, pair<Pt, Pt> st, pair<Pt, Pt> ed) {
	struct Edge {
		pair<Pt, Pt> e;
		int cost;
		Edge(pair<Pt, Pt> e = {Pt(), Pt()}, int cost = 0): e(e), cost(cost) {}
	};
	map<Pt, set<Pt>> seen;
	vector<Edge> q;
    int ret = 0;
    q.push_back(Edge(st, 0));
    while (true) {
    	vector<Edge> q2;
    	while (!q.empty()) {
    		auto u = q.back();
    		q.pop_back();
    		if (u.e == ed)
    			return ret;
    		if (seen[u.e.first].count(u.e.second))
    			continue;
    		seen[u.e.first].insert(u.e.second);
    		Edge v = u;
    		swap(v.e.first, v.e.second);
    		if (u.cost)
    			q2.push_back(v);
    		else
    			q.push_back(v);
    		const auto &adj = g[u.e.second];
    		int idx = 0;
    		for (; idx < adj.size(); idx++) {
    			if (adj[idx].first == u.e.first)
    				break;
			}
			v.e.second = adj[(idx+1)%adj.size()].first;
			v.cost = adj[(idx+1)%adj.size()].second;
			q.push_back(v);
		}
    	q.swap(q2), ret++;
	}
	return ret;
}
int main() {
	int n, sx, sy, ex, ey;
	const Pt shot(1, 2e+7);	// coprime, it will be no colinear pair of points
	while (scanf("%d %d %d %d %d", &n, &sx, &sy, &ex, &ey) == 5) {
		vector<Seg> segs(n);
		Pt st(sx, sy), ed(ex, ey);
		for (int i = 0; i < n; i++) {
			int xa, xb, ya, yb;
			scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
			segs[i] = Seg(Pt(xa, ya), Pt(xb, yb));
		}
		if (st == ed) {
			puts("0");
			continue;
		}
		set<Pt> S;
		for (int i = 0; i < n; i++)
			S.insert(segs[i].s), S.insert(segs[i].e);
		segs.push_back(Seg(st, st+shot));
		segs.push_back(Seg(ed, ed+shot));
		segs.push_back(Seg(Pt(-1.5e+7, 1e+7), Pt(1.5e+7, 1e+7)));
		for (auto pt : S)
			segs.push_back(Seg(pt, pt+shot));

		map<Pt, vector<pair<Pt, int>>> g;
		pair<Pt, Pt> se, ee;
		for (int i = 0; i < segs.size(); i++) {
			vector<Pt> a;
			a.push_back(segs[i].s);
			a.push_back(segs[i].e);
			for (int j = 0; j < segs.size(); j++) {
				if (i == j)	continue;
				Pt p = intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e);
				if (p.x != INF)
					a.push_back(p);
			}
			sort(a.begin(), a.end());
			a.resize(unique(a.begin(), a.end()) - a.begin());
			auto *prev = &g[a[0]];
			int c = (i < n);
			for (int j = 1; j < a.size(); j++) {
				prev->push_back({a[j], c});
				prev = &g[a[j]];
				prev->push_back({a[j-1], c});
			}
			if (i == n)	
				se = {a[0], a[1]};
			if (i == n+1)
				ee = {a[0], a[1]};
		}

		for (auto &e : g)
			sort(e.second.begin(), e.second.end(), AngleCmp(e.first));

        printf("%d\n", bfs(g, se, ee));
	}
	return 0;
}
/*

9 1 6 9 3
0 0 10 0
10 0 10 10
10 10 0 10
0 10 0 0
0 5 10 5
1 5 1 8
1 8 0 9
9 5 9 2
9 2 10 1

8 3 3 19 3
0 1 22 1
0 5 22 5
1 0 1 6
5 0 5 6
9 0 9 6
13 0 13 6
17 0 17 6
21 0 21 6

1 0 5 10 5
0 0 10 10
*/

