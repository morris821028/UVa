#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if (fabs(x-a.x) > eps)
            return x < a.x;
        if (fabs(y-a.y) > eps)
            return y < a.y;
        return false;
    }
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    bool operator==(const Pt &a) const {
    	return (fabs(x - a.x) < eps && fabs(y - a.y) < eps);
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
};
struct Seg {
	Pt s, e;
	Seg(Pt a = Pt(), Pt b = Pt()):
		s(a), e(b) {}
};
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
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
       cross(at, as, bs) * cross(at, as, bt) < 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
double distProjection(Pt as, Pt at, Pt s) {
	int a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
double ptToSeg(Seg seg, Pt p) {
	double c = 1e+30;
	if(between(seg.s, seg.e, p))
		c = min(c, distProjection(seg.s, seg.e, p));
	else
		c = min(c, min(dist(seg.s, p), dist(seg.e, p)));
	return c;
}
double getArea(Pt a, Pt b, Pt c) {
	return fabs(cross(a, b, c))/2.0;
}
int isEmptyTriangle(Pt a, Pt b, Pt c, Pt D[], int n) {
	for (int i = 0; i < n; i++) {
		if (D[i] == a || D[i] == b || D[i] == c)
			continue;
		if (cross(a, D[i], b) * cross(a, D[i], c) < 0 && 
			cross(b, D[i], a) * cross(b, D[i], c) < 0 &&
			cross(c, D[i], a) * cross(c, D[i], b) < 0)
			return 0;
	}
	return 1;
}
int main() {
	int testcase, n;
	Pt D[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			D[i].read();
		for (int i = 0; i < n; i++)
			D[i + n] = D[i];
		double dp[128][128];
		for (int i = 0; i < 2 * n; i++) {
			for (int j = 0; j < 2 * n; j++) {
				dp[i][j] = 1e+30;
			}
			dp[i][i] = dp[i][i+1] = 0;
		}
		double ret = 1e+30;
		for (int i = 2; i < n; i++) {
			for (int j = 0; j < n; j++) {// [j, j+i]
				int l = j, r = j + i;
				double &v = dp[l][r];
				for (int k = l+1; k < r; k++) {
					if (isEmptyTriangle(D[l], D[r], D[k], D, n))
						v = min(v, max(max(dp[l][k], dp[k][r]), getArea(D[l], D[r], D[k])));
				}
			}
		}
		for (int i = 0; i < n; i++)
			ret = min(ret, dp[i][i + n - 1]);
		printf("%.1lf\n", ret);
	}
	return 0;
}
/*
1
6
7 0
6 2
9 5
3 5
0 3
1 1
*/
