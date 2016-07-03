// dp, slower, TLE ! 
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <assert.h>
#include <queue>
#include <algorithm>
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
    double length2() {
        return x*x + y*y;
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
        // angle = atan2(e.y - s.y, e.x - s.x);
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
double distSeg2Point(Pt a, Pt b, Pt p) {
    Pt c, vab;
    vab = a - b;
    if (between(a, b, p)) {
        c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
        return (p - c).length();
    }
    return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
int cmpZero(double x) {
    if (fabs(x) < eps)  return 0;
    return x < 0 ? -1 : 1;
}
Pt projectLine(Pt as, Pt ae, Pt p) {
    double a, b, c, v;
    a = as.y - ae.y, b = ae.x - as.x;
    c = - (a * as.x + b * as.y);
    v = a * p.x + b * p.y + c;
    return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}
const double pi = acos(-1);

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
    	Pt A, B, o(0, 0);
    	double R;
    	
    	scanf("%lf %lf %lf %lf %lf", &A.x, &A.y, &R, &B.x, &B.y);
    	    		
		double L = (A - o).length();
		double theta = asin(R/L);
		double ret;
		Pt p1, p2, l1, l2;
		l1 = rotateRadian(A, theta);
		l2 = rotateRadian(A, -theta);
		p1 = projectLine(o, o + l1, B);
		p2 = projectLine(o, o + l2, B);
		
    	if (cmpZero(dot(A - B, o - B)) <= 0 || cmpZero(dot(A - o, B - o)) <= 0) {
    		printf("%.3lf\n", 0);
    		continue;
    	}
    	if (cmpZero(cross(o, o+l1, B)) == cmpZero(cross(o, o+l2, B))) {
    		printf("%.3lf\n", 0);
    		continue;
    	}
    	
		ret = min((p1 - B).length(), (p2 - B).length());
		ret = min(ret, (A - B).length() - R);
//		printf("pp %lf %lf %lf %lf\n", p1.x, p1.y, p2.x, p2.y);
		printf("%.3lf\n", ret + eps);
    }
    return 0;
}

/*
3
5 5 1 12 12
20 0 3 7 -7
-9.6 4.3 2.1 -19.2 7.9
*/
