#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;

struct Pt {
    double x, y;
    Pt() {}
    Pt(double a, double b): x(a), y(b) {}
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
    void read() {
    	scanf("%lf %lf", &x, &y);
	}
	double dist(Pt a) const {
		return sqrt(pow(x-a.x, 2)+pow(y-a.y, 2));
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

struct Seg {
    Pt s, e;
    Seg() {}
    Seg(Pt a, Pt b):s(a), e(b) {}
    void println() {
    	printf("Segment((%lf, %lf), (%lf, %lf))\n", s.x, s.y, e.x, e.y);
    }
    double dist(Seg o) const {
    	double ret = 1e+60;
    	ret = min(ret, this->dist(o.s));
    	ret = min(ret, this->dist(o.e));
    	ret = min(ret, o.dist(s));
    	ret = min(ret, o.dist(e));
    	return ret;
	}
	double dist(Pt p) const {
		if (between(s, e, p))
			return fabs(cross(s, e, p))/s.dist(e);
		return min(s.dist(p), e.dist(p));
	}
};
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    return cross(as, at, bs) * cross(as, at, bt) < 0 &&
    	cross(bs, bt, as) *cross(bs, bt, at) < 0;
}

struct Poly {
	vector<Pt> p;
	void read(int n) {
		Pt pt;
		p.clear();
		for (int i = 0; i < n; i++) {
			pt.read();
			p.emplace_back(pt);
		}
	}
	double dist(Poly &o) const {
		double ret = 1e+60;
		for (int i = p.size()-1, j = 0; j < p.size(); i = j++) {
			for (int a = o.p.size()-1, b = 0; b < o.p.size(); a = b++) {
				double d = Seg(p[i], p[j]).dist(Seg(o.p[a], o.p[b]));
				ret = min(ret, d);
			}
		}
		return ret;
	}
} poly[105];

struct Edge {
	int x, y;
	double w;
	Edge(int x, int y, double w): x(x), y(y), w(w) {}
	bool operator<(const Edge &o) const {
		return w < o.w;
	}
};

int parent[1024], weight[1024];
void init(int n) {
    for (int i = 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    if (weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}

int main() {
	int testcase;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &m);
			poly[i].read(m);
		}
		
		vector<Edge> E;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				double d = poly[i].dist(poly[j]);
				E.emplace_back(Edge(i, j, d));
			}
		}
		
		sort(E.begin(), E.end());
		init(n);
		double cost = 0;
		for (auto &e : E) {
			if (joint(e.x, e.y))
				cost += e.w;
		}
		printf("The minimal interconnect consists of %d bridges with a total length of %.3lf\n", n-1, cost);
	}
	return 0;
}
/*
1
3
4 0 0 0 1 1 1 1 0
4 2 0 2 1 3 1 3 0
3 4 0 5 0 5 1
*/
