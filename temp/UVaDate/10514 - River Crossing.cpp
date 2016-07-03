#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
using namespace std;
#define eps 1e-9
struct Pt {
    double x, y;
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
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Pt &a) const {
    	return !(a == *this);
	}
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	double length() {
		return hypot(x, y);
	}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
};
const double pi = acos(-1);
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
       cross(at, as, bs) * cross(at, as, bt) < 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
struct Seg {
	Pt s, e;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0): 
		s(a), e(b), label(l) {}
	bool operator!=(const Seg &other) const {
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
	return acos(dot(va, vb) / va.length() / vb.length());
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}
double distProjection(Pt as, Pt at, Pt s) {
	int a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
double dist2Seg(Pt sa, Pt sb, Pt p) {
    double c = 1e+30;
    if(between(sa, sb, p))
        c = min(c, distProjection(sa, sb, p));
    else
        c = min(c, min(dist(sa, p), dist(sb, p)));
    return c;
}
struct Poly {
	vector<Pt> p;
	int close;
	void read(int n, int c) {
		p.clear(), close = c;
		for (int i = 0; i < n; i++) {
			Pt v;
			v.read();
			p.push_back(v);
		}
	}
	double dist(const Poly &x) const {
		double ret = 1e+10;
		for (int i = 0, j = p.size()-1; i < p.size(); j = i++) {
			for (int a = 0, b = x.p.size()-1; a < x.p.size(); b = a++) {
				if (close || (!close && j != p.size()-1))
					ret = min(ret, dist2Seg(p[i], p[j], x.p[a]));
				if (x.close || (!x.close && b != x.p.size()-1))
					ret = min(ret, dist2Seg(x.p[a], x.p[b], p[i]));
			}
		}
		return ret;
	}
} island[32];
int main() {
	int testcase;
	int R1, R2, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &R1, &R2, &N);
		island[0].read(R1, 0);
		island[1].read(R2, 0);
		for (int i = 0, j = 2, m; i < N; i++, j++) {
			scanf("%d", &m);
			island[j].read(m, 1);
		}
		N += 2;
		
		double f[32][32];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)	f[i][j] = 0;
				else		f[i][j] = island[i].dist(island[j]);
			}
		}
		
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		}
		printf("%.3lf\n", f[0][1]);
	}
	return 0;
}

/*
3

15 14 0
0 9 7 7 10 7 16 11 20 12 24 11 25 9 24 4 25 2 31 1 38 3 41 11 44 15 49 17 51 17
0 19 3 20 8 19 11 19 15 21 21 23 25 23 26 20 26 18 34 19 37 21 42 23 47 24 51 24

15 14 4
0 9 7 7 10 7 16 11 20 12 24 11 25 9 24 4 25 2 31 1 38 3 41 11 44 15 49 17 51 17
0 19 3 20 8 19 11 19 15 21 21 23 25 23 26 20 26 18 34 19 37 21 42 23 47 24 51 24
4
5 11 9 11 7 15 4 14
3
17 14 16 16 19 17
3
28 15 33 13 30 17
6
31 5 27 7 29 12 31 8 35 9 34 6
 

2 2 0
0 0 1000 0
0 100 1000 100
*/
