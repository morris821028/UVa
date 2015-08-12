#include <bits/stdc++.h>
using namespace std;
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
    double length() {
    	return hypot(x, y);
    }
};
int main() {
	int A[8];
	while (true) {
		int end = 1;
		for (int i = 0; i < 8; i++) {
			scanf("%d", &A[i]);
			end &= A[i] == 0;
		}
		if (end)	return 0;
		Pt p[4];
		for (int i = 0; i < 8; i += 2)
			p[i/2] = Pt(A[i], A[i+1]);
		
		Pt ps = (p[0] + p[2]) * 0.5, pe = (p[1] + p[3]) * 0.5;
		double dx, dy, a, b, m1, m2;
		dx = floor((pe-ps).x);
		dy = floor((pe-ps).y);
		m1 = (p[2] - p[0]).y/(p[2] - p[0]).x;
		m2 = (p[3] - p[1]).y/(p[3] - p[1]).x;
		a = (p[1] - p[3]).length() / (p[0] - p[2]).length();
		b = atan((m2 - m1)/(1 + m1*m2));
		if (fabs(b) < 1e-3)	b = 0;
		printf("%d %d %.3lf %.3lf\n", (int)(pe-ps).x, (int)(pe-ps).y, a, b);
	}
	return 0;
}
