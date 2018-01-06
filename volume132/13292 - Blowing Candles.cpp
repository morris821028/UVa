#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)	return x < a.x;
        return y < a.y;
    }
    bool operator==(const Pt &a) const {
        return fabs(x-a.x) < eps && fabs(y-a.y) < eps;
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator/(const double val) const {
        return Pt(x / val, y / val);
    }
    Pt operator*(const double val) const {
        return Pt(x * val, y * val);
    }
};
typedef Pt Vector;
double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int cmpZero(double x) {  
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1: -1;
} 
double ptToLine(Pt p, Pt s, Pt e) {
	double area = fabs(cross(p, s, e));
	double h = area / dist(s, e);
	return h;
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for (int i = n-1, t = m+1; i >= 0; i--) {
        while (m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
double convex_width(Pt pt[], int n) {
	if (n <= 2)
		return 0;
	double ret = 1e+60;
	pt[n] = pt[0];
	// rotating caliper
	for (int i = 0, j = 0; i < n; i++) {
		while (cross(pt[i], pt[i+1], pt[j+1]) >= cross(pt[i], pt[i+1], pt[j]))
			j = (j+1)%n;
		double dist = ptToLine(pt[j], pt[i], pt[i+1]);
		ret = min(ret, dist);
	}
	return ret;
}
int main() {
	static const int MAXN = 262144;
	static Pt pt[MAXN], ch[MAXN];
	int n, m;
	int64_t r;
	while (scanf("%d %lld", &n, &r) == 2) {
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pt[i] = Pt(x, y);
		}
		m = monotone(n, pt, ch);
		double mn_width = convex_width(ch, m);
		printf("%.17lf\n", mn_width);
	}
	return 0;
}
/*
3  10
0  0
10  0
0  10
*/
