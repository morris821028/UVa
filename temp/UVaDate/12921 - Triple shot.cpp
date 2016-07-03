#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <assert.h>
#include <queue>
#include <algorithm>
using namespace std;
#define eps 1e-16
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

Pt circle(Pt &a, Pt &b, Pt &c) {
    Pt ab, ac;
   	double a1, b1, c1, a2, b2, c2, D, D1, D2;
    ab.x = (a.x+b.x)/2, ab.y = (a.y+b.y)/2;
    ac.x = (a.x+c.x)/2, ac.y = (a.y+c.y)/2;
    a1 = a.x-b.x, b1 = a.y-b.y;
    c1 = a1*ab.x + b1*ab.y;
    a2 = a.x-c.x, b2 = a.y-c.y;
    c2 = a2*ac.x + b2*ac.y;
    D = a1*b2-a2*b1;
    D1 = c1*b2-c2*b1;
    D2 = a1*c2-a2*c1;
    return Pt(D1/D, D2/D);
}

int main() {
	double x, y;
    while (scanf("%lf %lf", &x, &y) == 2) {
    	Pt a, b, c;
    	a = Pt(x, y);
    	b.read();
    	c.read();
		if (cross(a, b, c) == 0) {
    		puts("Impossible");
    	} else {
    		Pt o = circle(a, b, c);
    		printf("%.10lf %.10lf\n", o.x, o.y);
    	}
    }
    return 0;
}

/*
-4 0
0 4
4 0

1 2
2 4
4 8

0 0 
0 0
0 0

0 0
1 1
0 0

1 1
0 0
0 0

0 0
0 0
1 1
*/
