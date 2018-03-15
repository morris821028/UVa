#include <bits/stdc++.h> 
using namespace std;
const double eps = 1e-8;
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
void midPerimeter(double ab, double ac, double bc, double p2, 
	double bx, double by, double cx, double cy,
	double &dx, double &dy) {
	if (ab < ac) {
		dx = (p2-ab)/bc*(cx-bx)+bx;
		dy = (p2-ab)/bc*(cy-by)+by;
	} else {
		dx = (p2-ac)/bc*(bx-cx)+cx;
		dy = (p2-ac)/bc*(by-cy)+cy;
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		double ax, ay, bx, by, cx, cy;
		scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy);
		const double ab = hypot(ax-bx, ay-by);
		const double ac = hypot(ax-cx, ay-cy);
		const double bc = hypot(cx-bx, cy-by);
		const double p = (ab+ac+bc);
		const double p2 = p/2;
		double dx, dy, ex, ey, fx, fy;
		midPerimeter(ab, ac, bc, p2, bx, by, cx, cy, dx, dy);
		midPerimeter(ab, bc, ac, p2, ax, ay, cx, cy, ex, ey);
		midPerimeter(ac, bc, ab, p2, ax, ay, bx, by, fx, fy);
		fprintf(stderr, "%lf %lf\n", dx, dy);
		fprintf(stderr, "%lf %lf\n", ex, ey);
		fprintf(stderr, "%lf %lf\n", fx, fy);
		Pt c1 = getIntersect(Pt(ax, ay), Pt(dx, dy), Pt(bx, by), Pt(ex, ey));
		Pt c2 = getIntersect(Pt(cx, cy), Pt(fx, fy), Pt(bx, by), Pt(ex, ey));
		++cases;
		printf("Case %d: ", cases);
		if (c1 == c2)
			printf("%.6lf %.6lf\n", c1.x + eps, c2.y + eps);
		else
			puts("ERROR");
	}
	return 0;
}
/*
2
-1 0 1 0 0 1
0 0 5 0 3 3
*/
