#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-9
#define MAXN 131072
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
};
double dist(Pt a, Pt b) {
	return (a-b).length();
}
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
	return dot(c - a, b - a) > -eps && dot(c - b, a - b) > -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
	if (cross(as, at, bs) * cross(as, at, bt) < -eps &&
		cross(at, as, bs) * cross(at, as, bt) < -eps &&
		cross(bs, bt, as) * cross(bs, bt, at) < -eps &&
		cross(bt, bs, as) * cross(bt, bs, at) < -eps)
		return 1;
	return 0;
}
struct Seg {
	Pt s, e;
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
};
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(onSeg(p[i], p[j], q))
            return 1;
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}
double solve(Pt D[], int n, Pt s, Pt e) {
	vector<Pt> p;
	for (int i = 0, j = n - 1; i < n; j = i++) {
		if (cross(s, e, D[i]) * cross(s, e, D[j]) < -eps) {
			Pt t = getIntersect(Seg(D[i], D[j]), Seg(s, e));
			p.push_back(t);
		} else if (onSeg(s, e, D[i]) || fabs(cross(s, e, D[i])) < eps)
			p.push_back(D[i]);
	}
	p.push_back(s);
	p.push_back(e);
	sort(p.begin(), p.end());
	double ret = 0;
	for (int i = 0; i + 1 < p.size(); i++) {
		Pt mid = (p[i] + p[i+1]) * 0.5;
		if (inPolygon(D, n, mid))
			ret += dist(p[i], p[i+1]);
//		printf("%lf %lf ++++\n", p[i].x, p[i].y);
	}
	return ret;
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		Pt D[2048];
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &D[i].x, &D[i].y);
		Pt s, e;
		for (int i = 0; i < m; i++) {
			scanf("%lf %lf", &s.x, &s.y);
			scanf("%lf %lf", &e.x, &e.y);
			double ret = solve(D, n, s, e);
			printf("%.3f\n", ret);
		}
	}
	return 0;
}
/*
9 5
0 0
0 2
1 1
2 2
3 1
4 2
5 1
6 2
6 0
-1 2 7.5 1
0 1 6 1
0 1.5 6 1.5
0 2 6 1
0 0 0 2
4 9
0 0 
0 1
1 1
1 0
0 0 1 1
1 1 0 0
0 0 1 0
0 0 0.5 0
0 0.5 1 0.5
0 1 1 1
1 1 1 0
0.75 0.75 0.75 0.25
0 0.25 1 0.75
*/
