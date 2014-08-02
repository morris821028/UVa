#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
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
	Pt a, b, c, o;	
	while(true) {
		scanf("%lf %lf", &a.x, &a.y);
		scanf("%lf %lf", &b.x, &b.y);
		scanf("%lf %lf", &c.x, &c.y);
		if(a.x < 0)	break;
		o = circle((a + b)/2, (b + c)/2, (c + a)/2);
		printf("%lf %lf %lf\n", o.x, o.y, dist(o, (a + b)/2));
	}
	return 0;
}
