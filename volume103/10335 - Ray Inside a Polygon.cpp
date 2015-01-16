// I hate it, more eps adjust. 
#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
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
int same(Pt a, Pt b) {
	return fabs(a.x - b.x) < 0.005 && fabs(a.y - b.y) < 0.005;
}
int main() {
	Pt p[32];
	double theta;
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		Pt S, lvec;
		S.read();
		scanf("%lf", &theta);
		theta = theta * pi / 180;
		lvec = Pt(cos(theta), sin(theta));
		for (int i = 0; i < n; i++) // anti-clockwise
			p[i].read();
		
		int lost = 0;
		Seg on;
		for (int i = 0, j = n-1; i < n; j = i++) {
			Seg b(p[j], p[i]);
			if (onSeg(b.s, b.e, S))
				on = b;
		}
		for (int it = 0; it <= m; it++) { // #reflect.
			Seg pick = on, a(S, S + lvec);
			for (int i = 0, j = n-1; i < n; j = i++) {
				Seg b(p[j], p[i]);
				if (cmpZero(cross(a.s, a.e, b.s)) * cmpZero(cross(a.s, a.e, b.e)) <= 0) {
					if (b != pick) {
						pick = b;
						break;
					}
				}
			}

			Pt poj = getIntersect(pick, Seg(S, S + Pt(pick.s.y - pick.e.y, pick.e.x - pick.s.x)));
			Pt sym = S + (poj - S) * 2;
			S = getIntersect(a, pick);	
			lvec = S - sym;			
//			printf("%lf %lf %lf %lf\n", pick.s.x, pick.s.y, pick.e.x, pick.e.y);
//			printf("%lf %lf\n", S.x, S.y);
			if (same(S, pick.s) || same(S, pick.e)) {
				lost = 1;
				break;
			}
//			double r;
//			if (dot(pick.e - pick.s, lvec) <= 0)
//				r = getAngle(lvec, pick.e - pick.s);
//			else
//				r = getAngle(lvec, pick.s - pick.e);
//			lvec = rotateRadian(lvec, 2 * r);
			on = pick;
//			printf("it %d: %lf %lf\n", it, S.x, S.y);
//			printf("%lf %lf %lf %lf\n", lvec.x, lvec.y, poj.x, poj.y);
		}
		if (lost)
			puts("lost forever...");
		else {
			if (fabs(S.x) < eps && S.x < 0)
				S.x = - S.x;
			if (fabs(S.y) < eps && S.y < 0)
				S.x = - S.y;
			printf("%.2lf %.2lf\n", S.x, S.y);
		}
	}
	return 0;
}
/*
4 4
2.00 0.00 0.00
0.00 0.00
4.00 0.00
4.00 4.00
0.00 4.00
4 0
2.00 0.00 45.00
0.00 0.00
4.00 0.00
4.00 4.00
0.00 4.00
3 501
10.99 109 0
10 10
11 110
11 10

3 0
1 0 91
0 0
5 5
5 0

3 1
1 0 91
0 0
5 5
5 0

3 2
1 0 91
0 0
5 5
5 0

0 0
*/
