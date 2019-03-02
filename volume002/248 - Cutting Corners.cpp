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
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    return cross(as, at, bs) * cross(as, at, bt) < 0 &&
    	cross(bs, bt, as) *cross(bs, bt, at) < 0;
}
double interpolate_x(double y, Pt p1, Pt p2) {
    if (p1.y == p2.y) return min(p1.x, p2.x);
    return p1.x + (double) (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}

struct Rect {
	Pt p[4];
	Rect() {}
	Rect(Pt a, Pt b, Pt c, Pt d) {
		p[0] = a, p[1] = b, p[2] = c, p[3] = d;
	}
	int contain(Pt q) const {
		int c = 0;
		for (int i = 3, j = 0; j < 4; i = j++) {
			if ((p[i].y > q.y) != (p[j].y > q.y) &&
	            q.x < interpolate_x(q.y, p[i], p[j]))
	            c++;
		}
		return c&1;
	}
	int intersect(Pt a, Pt b) {
		if (contain(a) || contain(b))
			return 1;
		for (int i = 3, j = 0; j < 4; i = j++) {
//			if (a == obs[k].p[i] && b == obs[k].p[j])
//				break;
//			if (a == obs[k].p[j] && b == obs[k].p[i])
//				break;
			if (intersection(a, b, p[i], p[j]))
				return 1;
		}
		if (intersection(a, b, p[0], p[2]))
			return 1;
		if (intersection(a, b, p[1], p[3]))
			return 1;
		return 0;
	}
	void println() {
		printf("Polygon(");
		for (int i = 0; i < 4; i++) {
			printf("(%lf, %lf)%s", p[i].x, p[i].y, i==3 ? ")\n" : ",");
		}
	}
};

int test(Pt a, Pt b, Rect obs[], int n) {
	if (a == b)
		return 0;
	for (int i = 0; i < n; i++) {
		int cnt1 = 0, cnt2 = 0;
		for (int j = 0; j < 4; j++) {
			cnt1 += cross(a, b, obs[i].p[j]) >= -eps;
			cnt2 += cross(a, b, obs[i].p[j]) <= eps;
		}
		if (cnt1 == 4 || cnt2 == 4)
			continue;
		if (obs[i].intersect(a, b))
			return 0;
	}
	return 1;
}

double dijkstra(int st, int ed, const vector<pair<int, double>> g[], int n) {
    typedef pair<double, int> PLL;
    vector<double> dist(n, 1e+60);
    set<PLL> pQ;
    pQ.insert(PLL(0, st)), dist[st] = 0;
    while (!pQ.empty()) {
        PLL u = *pQ.begin(); pQ.erase(pQ.begin());
        for (auto &e : g[u.second]) {
        	if (dist[e.first] > dist[u.second] + e.second) {
				if (dist[e.first] != 1e+60)
					pQ.erase(pQ.find(PLL(dist[e.first], e.first)));
				dist[e.first] = dist[u.second] + e.second;
				pQ.insert(PLL(dist[e.first], e.first));
			}
		}
	}
	assert(dist[ed] < 1e+60);
	return dist[ed];
}

int main() {
	int n;
	int cases = 0;
	double x, y;
	while (scanf("%d", &n) == 1 && n >= 0) {
		Pt st, ed;
		Rect obs[32];
		map<Pt, int> R;
		assert(n <= 20);
		st.read(), ed.read();
		R[st] = -1, R[ed] = -1;
		for (int i = 0; i < n; i++) {
			Pt a[3];
			for (int j = 0; j < 3; j++)
				a[j].read();
			int t = 0;
			for (int j = 0; j < 3; j++) {
				if (cmpZero(dot(a[(j+1)%3]-a[j], a[(j+2)%3]-a[j])) == 0) {
					obs[i] = Rect(a[j], a[(j+2)%3], a[(j+2)%3]+a[(j+1)%3]-a[j], a[(j+1)%3]);
					t++;
				}					
			}
			assert(t == 1);
			for (int j = 0; j < 4; j++)
				R[obs[i].p[j]] = -1;
		}

		int idx = 0;
		for (auto &e : R)
			e.second = idx++;
		
		int gn = idx;
		vector<pair<int, double>> g[505];
		for (auto u : R) {
			for (auto v : R) {
				if (u.second < v.second && test(u.first, v.first, obs, n)) {
					double d = u.first.dist(v.first);
					g[u.second].emplace_back(v.second, d);
					g[v.second].emplace_back(u.second, d);
				}
			}
		}
		double ret = dijkstra(R[st], R[ed], g, gn);
		if (cases)	puts("");
		printf("Scenario #%d\n", ++cases);
		printf("   route distance: %.2lf\n", ret);
	}
	return 0;
}
/*
5
6.5   9     10  3
1     5     3   3     6  6
5.25  2     8   2     8  3.5
6     10    6   12    9  12
7     6     11  6     11 8
10    7     11  7     11 11
-1

2
4 2 4 7
0 8 0 0 4 0
4 4 4 5 5 5

0
4 3 3 7

1
0 0 4 4
0 0 4 4 4 0

-1

18
83 9 277 993
161 439 194 439 161 441
97 233 112 233 97 264
430 529 479 529 430 563
549 437 576 437 549 519
704 546 778 546 704 608
449 160 461 160 449 175
479 600 540 600 479 649
123 95 169 95 123 142
117 629 145 629 117 704
61 26 125 26 61 69
151 37 167 37 151 70
241 184 296 184 241 261
590 319 651 319 590 341
692 305 693 305 692 389
700 273 788 273 700 290
13 534 32 534 13 565
425 315 460 315 425 365
397 501 441 501 397 582
*/ 
