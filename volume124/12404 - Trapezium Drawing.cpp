#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-6
#define MAXN 131072
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
	bool operator==(const Pt &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	} 
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
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
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}

double solve(double a, double b, double c, double d) {
	// d^2 - x^2 = b^2 - (a - x - c)^2
	// d^2 - x^2 = b^2 - (a-c - x)^2
	// d^2 - x^2 = b^2 - ((a-c)^2 - 2(a-c)x + x^2)
	// d^2 - x^2 = b^2 - (a-c)^2 + 2(a-c)x - x^2
	// d^2 - b^2 + (a-c)^2 = 2(a-c)x
	double x;
	x = (pow(d, 2) - pow(b, 2) + pow(a-c, 2))/(2 * (a-c));
	return x;
}
int main() {
	int testcase, cases = 0;
	double x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		Pt A, B, C, D;
		double a, b, c, d;
		scanf("%lf %lf", &x, &y);
		A = Pt(x, y);
		scanf("%lf %lf", &x, &y);
		B = Pt(x, y);
		scanf("%lf %lf %lf", &b, &c, &d);
		a = dist(A, B);
		x = solve(a, b, c, d);
		
		Pt vAB = (B - A) / a;
		double theta = atan2(sqrt(d*d - x*x), x);
		D = rotateRadian(vAB, theta) * d + A;
		C = D + vAB * c;
		printf("Case %d:\n", ++cases);
		printf("%.8lf %.8lf %.8lf %.8lf\n", C.x, C.y, D.x, D.y);
	}
	return 0;
}
/*
1
0 0 20 0 10 14 8

8
0 0 20 0 10 14 8
0 0 20 0 8 14 10
20 0 0 0 10 14 8
20 0 0 0 8 14 10
8 0 8 20 10 14 8
8 0 8 20 8 14 10
0 20 0 0 10 14 8
0 20 0 0 8 14 10
*/
