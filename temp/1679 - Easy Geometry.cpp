#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <assert.h>
#include <vector>
using namespace std;
#define eps 1e-8
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
	void read() {
		scanf("%lf %lf", &x, &y);
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
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
//		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
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
const double pi = acos(-1);
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
#define MAXN 131072
#define INF 1e+30
Pt D[MAXN];
double ret;
Pt retLpt, retRpt;
double getArea(vector<Pt> &upper, vector<Pt> &lower, double lx, double rx) {
	int p, q;
	Pt a, b, c, d;
	p = (int) (lower_bound(upper.begin(), upper.end(), Pt(lx, INF)) - upper.begin());
	q = (int) (lower_bound(lower.begin(), lower.end(), Pt(lx, INF)) - lower.begin());
	assert(p > 0 && q > 0);
	a = getIntersect(Seg(Pt(lx, 1), Pt(lx, -1)), Seg(upper[p], upper[p-1]));
	b = getIntersect(Seg(Pt(lx, 1), Pt(lx, -1)), Seg(lower[q], lower[q-1]));
	p = (int) (lower_bound(upper.begin(), upper.end(), Pt(rx, INF)) - upper.begin());
	q = (int) (lower_bound(lower.begin(), lower.end(), Pt(rx, INF)) - lower.begin());
	assert(p > 0 && q > 0);
	c = getIntersect(Seg(Pt(rx, 1), Pt(rx, -1)), Seg(upper[p], upper[p-1]));
	d = getIntersect(Seg(Pt(rx, 1), Pt(rx, -1)), Seg(lower[q], lower[q-1]));
	double area = (rx - lx) * (min(a.y, c.y) - max(b.y, d.y));
	if (area > ret) {
		ret = area;
		retLpt = Pt(lx, max(b.y, d.y));
		retRpt = Pt(rx, min(a.y, c.y));
	}
	return area;
}
double search(vector<Pt> &upper, vector<Pt> &lower, double lx) {
	double l = lx, r = upper[upper.size()-1].x, mid, midmid, md, mmd;
	double ret = 0;
	for (int it = 0; it < 100; it++) {
		mid = (l + r)/2;
		midmid = (mid + r)/2;
		md = getArea(upper, lower, lx, mid);
		mmd = getArea(upper, lower, lx, midmid);
		ret = max(ret, md);
		if (md < mmd)
			l = mid;
		else
			r = midmid;
	}
	return ret;
}
double findMaxRectangle(vector<Pt> upper, vector<Pt> lower) {
	double mnx, mxx;
	mnx = upper[0].x, mxx = upper[upper.size()-1].x;
	double l = mnx, r = mxx, mid, midmid, md, mmd;
	double ret = 0;
	for (int it = 0; it < 100; it++) {
		mid = (l + r)/2;
		midmid = (mid + r)/2;
		md = search(upper, lower, mid);
		mmd = search(upper, lower, midmid);
		ret = max(ret, md);
		if (md < mmd)
			l = mid;
		else
			r = midmid;
	}
	return ret;
}
int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			D[i].read(); // clockwise order
		double mnx = INF, mxx = -INF;
		for (int i = 0; i < N; i++) {
			mnx = min(mnx, D[i].x);
			mxx = max(mxx, D[i].x);
		}
		vector<Pt> upper, lower;
		Pt Lpt = Pt(mnx, -INF), Rpt = Pt(mxx, INF);
		int lst, rst;
		for (int i = 0; i < N; i++) {
			if (cmpZero(D[i].x - mnx) == 0) {
				if (Lpt < D[i]) {
					Lpt = D[i], lst = i;
				}
			}
			if (cmpZero(D[i].x - mxx) == 0) {
				if (D[i] < Rpt) {
					Rpt = D[i], rst = i;
				}
			}
		}
		while (true) {
			upper.push_back(D[lst]);
			if (cmpZero(D[lst].x - mxx) == 0)
				break;
			lst = (lst + 1)% N;
		}
		while (true) {
			lower.push_back(D[rst]);
			if (cmpZero(D[rst].x - mnx) == 0)
				break;
			rst = (rst + 1)% N;
		}
		reverse(lower.begin(), lower.end());
		ret = 0;
		double area = findMaxRectangle(upper, lower);
//		printf("%lf\n", area);
		printf("%lf %lf %lf %lf\n", retLpt.x, retLpt.y, retRpt.x, retRpt.y);
	}
	return 0;
}
/*
4
5 1
2 4
3 7
7 3
5
1 1
1 4
4 7
7 4
7 1
*/
