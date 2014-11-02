#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator/(const double a) const {
        return Pt(x/a, y/a);
    }
};
double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
}
double dist2(Pt a, Pt b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
double length(Pt a) {
    return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double angle(Pt a, Pt b) {
    return acos(dot(a, b) / length(a) / length(b));
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
}
Pt getIntersection(Pt p, Pt l1, Pt q, Pt l2) {
    double a1, a2, b1, b2, c1, c2;
    double dx, dy, d;
    a1 = l1.y, b1 = -l1.x, c1 = a1 * p.x + b1 * p.y;
    a2 = l2.y, b2 = -l2.x, c2 = a2 * q.x + b2 * q.y;
    d = a1 * b2 - a2 * b1;
    dx = b2 * c1 - b1 * c2;
    dy = a1 * c2 - a2 * c1;
    return Pt(dx / d, dy / d);
}
Pt circle(Pt a, Pt b, Pt c) {
    Pt mab = (a + b)/2;
    Pt mbc = (b + c)/2;
    Pt lab = b - a, lbc = c - b;
    swap(lab.x, lab.y);
    swap(lbc.x, lbc.y);
    lab.x = -lab.x;
    lbc.x = -lbc.x;
    return getIntersection(mab, lab, mbc, lbc);
}

int main() {
    Pt a, b, c, p;
    int cases = 0;
    while (scanf("%lf %lf", &a.x, &a.y) == 2) {
        scanf("%lf %lf", &b.x, &b.y);
        scanf("%lf %lf", &c.x, &c.y);
        scanf("%lf %lf", &p.x, &p.y);
        double ret = min(dist(p, a), dist(p, c));
        double a1, b1, c1;
        Pt o = circle(a, b, c);
        a1 = a.y - c.y, b1 = c.x - a.x, c1 = a1 * a.x + b1 * a.y; // line ac
//        printf("%lf %lf %lf\n", a1, b1, c1);
//        printf("%lf %lf\n", a1 * b.x + b1 * b.y - c1, a1 * p.x + b1 * p.y - c1);
//        printf("%lf %lf\n", o.x, o.y);
        if ((a1 * b.x + b1 * b.y - c1 > 0) == (a1 * o.x + b1 * o.y - c1 > 0)) {
            double d = dist(o, p), r = dist(o, a);
            if ((a1 * b.x + b1 * b.y - c1 > 0) == (a1 * p.x + b1 * p.y - c1 > 0)) {
                if (cross(a, c, p) * cross(a, o, p) < eps &&
                    cross(c, o, p) * cross(c, a, p) < eps &&
                    cross(o, a, p) * cross(o, c, p) < eps) {
                } else {
                    if (d > r)
                        d -= r;
                    else
                        d = r - d;
                    ret = min(ret, d);
                }
            } else {
                if (cross(o, a, p) * cross(o, c, p) > -eps) {
                    d = d - r;
                    ret = min(ret, d);
                }
            }
        } else {
            double d = dist(o, p), r = dist(o, a);
            if ((a1 * b.x + b1 * b.y - c1 > 0) == (a1 * p.x + b1 * p.y - c1 > 0)) {
            	if (cross(o, a, p) * cross(o, c, p) < eps) {
	                if (d > r)
	                    d -= r;
	                else
	                    d = r - d;
	                ret = min(ret, d);
            	}
            } else {
                if (cross(a, c, p) * cross(a, o, p) < eps &&
                        cross(c, o, p) * cross(c, a, p) < eps &&
                        cross(o, a, p) * cross(o, c, p) < eps) {
                    d = r - d;
                    ret = min(ret, d);
                }
            }
        }
        assert(ret >= 0);
        printf("Case %d: %.3lf\n", ++cases, ret + eps);
    }
    return 0;
}
/*
 4 -2 -2 4 -4 -2 -1 3 
 4 -2 -2 4 -4 -2 1 3
 4 -2 -2 4 -4 -2 -3 5 
 4 -2 -2 4 -4 -2 3 5
 4 -2 -2 4 -4 -2 -3 1
 4 -2 -2 4 -4 -2 -5 1 
 4 -2 -2 4 -4 -2 -1 -1
 4 -2 -2 4 -4 -2 -1 -3 
 4 -2 -2 4 -4 -2 0 0 
 
 -4 3 0 5 4 3 9 4 
 -4 3 0 5 4 3 -9 4
 -4 3 0 5 4 3 10 3
 -4 3 0 5 4 3 -4 5
 -4 3 0 5 4 3 8 2
 -4 3 0 5 4 3 1 2
 -4 3 0 5 4 3 1 -2
 -4 3 0 5 4 3 2 1

 0 0 1 1 2 0 1 -1
 
 3 4 0 5 -3 4 0 1
 3 4 0 5 -3 4 0 4.5
 3 4 0 5 -3 4 1 3
 3 4 0 5 -3 4 -3 3
 3 4 0 5 -3 4 0 -1
 
 -1 -1 0 3 1 -1 1 1
 -1 -1 0 3 1 -1 -2 -1
 -1 -1 0 3 1 -1 0 0
 -1 -1 0 3 1 -1 0 -1
 -1 -1 0 3 1 -1 0 -2
 
 2 0 0 2 -2 0 0 0
 
 Case 1: 1.414
 Case 2: 4.000
 Case 3: 0.500
 Case 4: 1.838
 Case 5: 1.000
 Case 6: 5.831
 Case 7: 1.117
 Case 8: 0.616
 Case 9: 1.414
*/
