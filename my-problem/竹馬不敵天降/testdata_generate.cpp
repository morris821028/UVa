#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map> 
#include <functional>
#include <math.h>
#include <string.h>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x < a.x;
        if(fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator>(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x > a.x;
        if(fabs(y - a.y) > eps)	return y > a.y;
        return false;
    }
    bool operator!=(const Pt &a) const {
        return fabs(x - a.x) > eps || fabs(y - a.y) > eps;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    void print() const {
    	double px = x, py = y;
    	if (fabs(x) < eps)	px = 0;
    	if (fabs(y) < eps)	py = 0;
    	printf("%.6lf %.6lf\n", px, py);
    }
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
    if(cross(as, at, bs) * cross(as, at, bt) <= 0 &&
       cross(at, as, bs) * cross(at, as, bt) <= 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}
Pt intersectionPt(Pt as, Pt at, Pt bs, Pt bt) {
	double a1, a2, b1, b2, c1, c2, dx, dy, d;
	a1 = as.y - at.y, b1 = -(as.x - at.x), c1 = as.x * a1 + as.y * b1;
	a2 = bs.y - bt.y, b2 = -(bs.x - bt.x), c2 = bs.x * a2 + bs.y * b2;
	dx = c1 * b2 - c2 * b1;
	dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
    return Pt(dx/d, dy/d);
}
int checkIntersectionPt(Pt as, Pt at, Pt bs, Pt bt) {
	double a1, a2, b1, b2, c1, c2, dx, dy, d;
	a1 = as.y - at.y, b1 = -(as.x - at.x), c1 = as.x * a1 + as.y * b1;
	a2 = bs.y - bt.y, b2 = -(bs.x - bt.x), c2 = bs.x * a2 + bs.y * b2;
	dx = c1 * b2 - c2 * b1;
	dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
	return fabs(d) < eps;
}
struct seg {
	Pt s, e;
	seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
	bool operator<(const seg &a) const {
        if (s != a.s)	return s < a.s;
        return e < a.e;
    }
};
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 10;
	while(T--) {
		n = 100, a = 1000, b = 1000;
		printf("%d %d %d\n", n, a, b);
		set< pair<int, int> > S;
		for (int i = 0; i < n; i++) {
			do {
				x = rand()%(a+1), y = rand()%(b+1);
				if (S.find(make_pair(x, y)) == S.end())
					break;
			} while (true);
			printf("%d %d\n", x, y);
			S.insert(make_pair(x, y));
		}
		puts("");
	}
	return 0;
}
