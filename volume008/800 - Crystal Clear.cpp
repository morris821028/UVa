#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

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
//		printf("dist %lf %lf %lf\n", x-a.x, y-a.y, hypot(x-a.x, y-a.y));
		return hypot(x-a.x, y-a.y);
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
		if (between(s, e, p)) {
//			printf("%lf %lf\n", cross(s, e, p), s.dist(e));
			return fabs(cross(s, e, p))/s.dist(e);
		}
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

double interpolate_x(double y, Pt p1, Pt p2) {
    if (p1.y == p2.y) return p1.x;
    return p1.x + (double) (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}

int inside(Pt p[], int n, Pt q) {
	int c = 0;
	double tx = q.x, ty = q.y;
	for (int i = n-1, j = 0; j < n; i = j++) {
		if ((p[i].y > ty) != (p[j].y > ty) &&
            tx < interpolate_x(ty, p[i], p[j]))
            c++;
        if (onSeg(p[i], p[j], q))
        	return 1;
	}
	return c&1;
}

double dist_retain(Pt p[], int n, Pt q) {
	double ret = 1e+60;
	for (int i = n-1, j = 0; j < n; i = j++) {
		double d = Seg(p[i], p[j]).dist(q);
		if (d < 0.5-eps && d > eps)
			return -1;
		ret = min(ret, d);
	}
	return ret;
}


int main() {
	int cases = 0;
	int n;
	Pt p[25];
	const double pi = acos(-1);
	while (scanf("%d", &n) == 1 && n) {
		int lx = INT_MAX, ly = INT_MAX;
		int rx = INT_MIN, ry = INT_MIN;
		set<Pt> S;
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			p[i] = Pt(x, y);
			lx = min(lx, x), ly = min(ly, y);
			rx = max(rx, x), ry = max(ry, y);
			S.insert(p[i]);
		}
						
		double full = 0;
		double half = 0;
		for (int i = lx; i <= rx; i++) {
			for (int j = ly; j <= ry; j++) {
				if (S.count(Pt(i, j)))
					continue;
				if (inside(p, n, Pt(i, j))) {
					double d = dist_retain(p, n, Pt(i, j));
					if (d >= 0.5) {
						full++;
					} else if (cmpZero(d) == 0) {
						half++;
					}
				}
			}
		}
		
		double area = 0;
		for (int i = 0; i < n; i++) {
			double d = dist_retain(p, n, p[i]);
			if (d < 0)
				continue;
			Pt q = p[(i-1+n)%n];
			Pt r = p[(i+1)%n];
			double theta = acos(dot(q-p[i], r-p[i])/p[i].dist(q)/p[i].dist(r));
			area += theta/8;
		}
		half = half*0.5;
		double sum = (full + half) * pi/4 + area;
		printf("Shape %d\n", ++cases);
		printf("Insulating area = %.3lf cm^2\n", sum);
	}
	return 0;
}

/*
5
0 2
3 5
6 3
6 0
1 0
3
-250 0
250 1
250 0

3
0 0
0 1
0 2

3
-69 6
221 164
43 67
0
*/
