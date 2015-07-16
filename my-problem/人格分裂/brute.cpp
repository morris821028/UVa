#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;
#define eps 1e-12 
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
};
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
struct seg {
	Pt s, e;
	int label;
	seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
};
struct CMPDOUBLE {
	bool operator()(const double &i, const double &j) {
		if (fabs(i-j) > eps)
			return i < j;
		return false;
	}
};
const double pi = acos(-1);
Pt getIntersect(Pt l1, Pt p1, Pt l2, Pt p2) {
	double a1, b1, c1, a2, b2, c2;
	double dx, dy, d;
	a1 = l1.y, b1 = -l1.x;
	c1 = a1 * p1.x + b1 * p1.y;
	a2 = l2.y, b2 = -l2.x;
	c2 = a2 * p2.x + b2 * p2.y;
	dx = c1 * b2 - c2 * b1, dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
	return Pt(dx/d, dy/d);
}
int testMin(seg D[], int n, double theta) {
	int ret = -1;
	double mn = 1e+60;
	Pt o(0, 0), p(cos(theta), sin(theta));
	for (int i = 0; i < n; i++) {
		if (cross(o, p, D[i].s) * cross(o, p, D[i].e) < eps) {
			Pt q = getIntersect(D[i].s - D[i].e, D[i].s, p, o);
			if (dot(q - o, p - o) > eps)
			if (q.x * q.x + q.y * q.y < mn)
				ret = D[i].label, mn = q.x * q.x + q.y * q.y;
		}
	}
	return ret;
}
int main() {	
	freopen("in.txt", "r+t", stdin);
	freopen("bruteout.txt", "w+t", stdout);
	int n;
	double sx, sy, ex, ey;
	Pt pos;
	seg D[32767];
	while (scanf("%d", &n) == 1) {
		int visual[32767] = {};
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
			D[i] = seg(Pt(sx, sy), Pt(ex, ey));
			D[i].label = i;
		}
		set<double, CMPDOUBLE> angle;
		for (int i = 0; i < n; i++) {
			double v1 = atan2(D[i].s.y, D[i].s.x);
			double v2 = atan2(D[i].e.y, D[i].e.x);
			angle.insert(v1), angle.insert(v2);
		}
		angle.insert(pi), angle.insert(-pi);
		vector<double> theta(angle.begin(), angle.end());
		for (int i = 1; i < theta.size(); i++) {
			double t = (theta[i] + theta[i-1])/2.0; // y = (tan t) x
			int v = testMin(D, n, t);
			if (v >= 0)
				visual[v] = 1;
		}
		int v = testMin(D, n, pi);
		if (v >= 0)
			visual[v] = 1;
		for (int i = 0; i < n; i++)
			printf("%d%s", visual[i], i == n-1 ? "" : " ");
		puts("");
	}
	return 0;
}
/*
1
5 -5 5 5

4
4 2 5 -2
2 4 6 1
5 5 8 1
3 -4 7 -1

7
-1 2 3 1
2 4 5 -1
-3 -1 1 -2
-1 -4 3 -2
-2 -4 1 -5
-4 1 -1 4
-3 4 -4 3

1
1 1 2 2

2
-1 3 -2 -2
-2 -1 -3 -1 
 
*/

