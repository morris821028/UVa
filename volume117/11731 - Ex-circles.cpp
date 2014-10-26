#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define eps 1e-6
const double pi = acos(-1); 
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
    Pt operator*(const double &a) const {
        return Pt(x * a, y * a);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
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
double getGrayArea(Pt A, Pt B, Pt C) {
	double r = fabs(cross2(B - A, C - A)) / dist(B, C);
	double radBAC = angle(B - A, C - A);
	return r * r * radBAC /2;
}
int main() {
	int cases = 0;
	double a, b, c;
	while(scanf("%lf %lf %lf", &a, &b, &c) == 3 && a+b+c) {
		Pt A, B, C, D, E, F;
		double radBAC = acos((b*b + c*c - a*a)/(2*b*c));
		double radABC = acos((a*a + c*c - b*b)/(2*a*c));
		double radACB = acos((a*a + b*b - c*c)/(2*a*b));
		A = Pt(0, 0);
		B = Pt(c, 0);
		C = A + rotateRadian(Pt(1, 0), radBAC) * b;
		double t1, t2, t3;
		t1 = (pi - radBAC)/2;
		t2 = (pi - radABC)/2;
		t3 = (pi - radACB)/2;
		Pt divA, divB, divC;
		divA = rotateRadian(C - A, t1); 
		divB = rotateRadian(B - A, t2);
		divC = rotateRadian(C - B, t3);
		D = getIntersection(A, divA, C, divC);
		E = getIntersection(B, divB, C, divC);
		F = getIntersection(A, divA, B, divB);
//		printf("%lf %lf, %lf %lf, %lf %lf\n", A.x, A.y, B.x, B.y, C.x, C.y);
//		printf("%lf %lf, %lf %lf, %lf %lf\n", D.x, D.y, E.x, E.y, F.x, F.y);
		double area = fabs(cross2(E - D, F - D))/2;
		double gray = getGrayArea(D, A, C) + getGrayArea(E, B, C) + getGrayArea(F, A, B);
		printf("Case %d: %.2lf %.2lf\n", ++cases, area, gray);
	}
	return 0;
}
/*
3 4 5
10 11 12
*/
