#include <bits/stdc++.h>
using namespace std;

/*
https://en.wikipedia.org/wiki/Malfatti_circles#Radius_formula
*/

#define eps 1e-12
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
    Pt operator/(const double a) const {
        return Pt(x / a, y / a);
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
    double dist2(Pt a) {
    	return (x - a.x)*(x - a.x)+(y - a.y)*(y - a.y);
    }
    double dist(Pt a) {
    	return sqrt(dist2(a));
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
Pt getIntersect(Pt as, Pt ae, Pt bs, Pt be) {
    Pt u = as - bs;
    double t = cross2(be - bs, u)/cross2(ae - as, be - bs);
    return as + (ae - as) * t;
}

void malfatti(Pt A, Pt B, Pt C) {
	double a, b, c, d, e, f;
	double r, s;
	double r1, r2, r3;
	Pt incenter;
	
	a = B.dist(C);
	b = A.dist(C);
	c = A.dist(B);
	s = (a+b+c)/2;
	incenter = (A*a + B*b + C*c)/(a+b+c);
	r = fabs(cross(A, B, C))/(a+b+c);
	d = incenter.dist(A);
	e = incenter.dist(B);
	f = incenter.dist(C);
	r1 = r*(s+d-r-e-f)/2/(s-a);
	r2 = r*(s+e-r-d-f)/2/(s-b);
	r3 = r*(s+f-r-d-e)/2/(s-c);
	printf("%.6lf %.6lf %.6lf\n", r1, r2, r3);
}
int main() {
	int a, b, c, d, e, f;
	while (scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f) == 6) {
		if (!a && !b && !c && !d && !e && !f)
			return 0;
		Pt A(a, b), B(c, d), C(e, f);
		malfatti(A, B, C);
	}
	return 0;
}
/*
20 80 -40 -20 120 -20
20 -20 120 -20 -40 80
0 0 1 0 0 1
0 0 999 1 -999 1
897 -916 847 -972 890 -925
999 999 -999 -998 -998 -999
-999 -999 999 -999 0 731
-999 -999 999 -464 -464 999
979 -436 -955 -337 157 -439
0 0 0 0 0 0
*/
