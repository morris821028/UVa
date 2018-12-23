#include <bits/stdc++.h>
using namespace std;

const float eps = 1e-6;
struct Pt {
    double x, y;
    Pt() {}
    Pt(double a, double b): x(a), y(b) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y); }
    Pt operator*(const double a) const { return Pt(x * a, y * a);  }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    void println() const {
    	printf("(%lf, %lf)\n", x, y);
    }
    Pt normal() {
    	double len = hypot(x, y);
    	return Pt(x/len, y/len);
	}
};
struct Seg {
    Pt s, e;
    Seg() {}
    Seg(Pt a, Pt b):s(a), e(b) {}
    void println() {
    	printf("Segment((%lf, %lf), (%lf, %lf))\n", s.x, s.y, e.x, e.y);
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
int cmpZero(float v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		double offset;
		scanf("%lf", &offset);
		scanf("%d", &n);
		Pt pt[16];
		for (int i = 0; i < n; i++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			pt[i] = Pt(x, y);
		}

		printf("%d\n", n);
		for (int i = 0, j = n-1; i < n; j = i++) {
			int k = (i+1)%n;
			Pt p = pt[j], q = pt[i], r = pt[k];
			Pt pq = (p-q).normal();
			Pt qr = (r-q).normal();
			Pt npq = Pt(pq.y, -pq.x);
			Pt nqr = Pt(-qr.y, qr.x);
			Seg s_pq = Seg(p+npq*offset, q+npq*offset);
			Seg s_qr = Seg(q+nqr*offset, r+nqr*offset);
			Pt ret = getIntersect(s_pq, s_qr);
			printf("%.3lf %.3lf\n", ret.x, ret.y);
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
1.0
5
10.0 5.0
10.0 3.0
3.0 3.0
3.0 6.0
5.0 8.0
*/
