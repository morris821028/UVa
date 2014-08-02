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
	Pt operator-(const Pt &a) const {
		Pt ret;
		ret.x = x - a.x;
		ret.y = y - a.y;
        return ret;
    }
};
enum LINE_TYPE {LINE, SEGMENT};
struct LINE2D {
    Pt s, e;
    LINE_TYPE type;
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
double onSeg(Pt a, Pt b, Pt c) {
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
double closest(LINE2D l1, LINE2D l2) {
	if(l1.type == SEGMENT && l2.type == SEGMENT) {
		if(intersection(l1.s, l1.e, l2.s, l2.e))
			return 0;
		double c = 1e+30;
		if(between(l1.s, l1.e, l2.s))
			c = min(c, distProjection(l1.s, l1.e, l2.s));
		else
			c = min(c, min(dist(l1.s, l2.s), dist(l1.e, l2.s)));
			
		if(between(l1.s, l1.e, l2.e))
			c = min(c, distProjection(l1.s, l1.e, l2.e));
		else
			c = min(c, min(dist(l1.s, l2.e), dist(l1.e, l2.e)));
		/* opposite */
		if(between(l2.s, l2.e, l1.s))
			c = min(c, distProjection(l2.s, l2.e, l1.s));
		else
			c = min(c, min(dist(l1.s, l2.s), dist(l1.e, l2.s)));
			
		if(between(l2.s, l2.e, l1.e))
			c = min(c, distProjection(l2.s, l2.e, l1.e));
		else
			c = min(c, min(dist(l2.s, l1.e), dist(l2.e, l1.e)));
		return c;
	}
	if(l1.type == LINE && l2.type == LINE) {
		double a1, a2, b1, b2, c1, c2;
		a1 = l1.s.y - l1.e.y;
		b1 = l1.e.x - l1.s.x;
		c1 = - (a1 * l1.s.x + b1 * l1.s.y);
		a2 = l2.s.y - l2.e.y;
		b2 = l2.e.x - l2.s.x;
		c2 = - (a2 * l2.s.x + b2 * l2.s.y);
		if(a1 * b2 - a2 * b1 != 0)
			return 0;
		return distProjection(l1.s, l1.e, l2.s);
	}
	if(l1.type != l2.type) {
		if(l1.type == SEGMENT)
			swap(l1, l2);
		/* l1 LINE, l2 SEGMENT*/
		double a1, b1, c1;
		a1 = l1.s.y - l1.e.y;
		b1 = l1.e.x - l1.s.x;
		c1 = - (a1 * l1.s.x + b1 * l1.s.y);
		int v1, v2;
		v1 = a1 * l2.s.x + b1 * l2.s.y + c1;
		v2 = a1 * l2.e.x + b1 * l2.e.y + c1;
		if(v1 * v2 <= 0)
			return 0; // different side
		return min(distProjection(l1.s, l1.e, l2.s), distProjection(l1.s, l1.e, l2.e));
	}
	return -1;
}
int main() {
	int n;
	double L, H;
	LINE2D D[1024];
	while(scanf("%d", &n) == 1) {
		scanf("%lf %lf", &L, &H);
		for(int i = 0; i < n; i++) {
			D[i].s.x = i&1 ? L : 0;
			scanf("%lf %lf %lf", &D[i].s.y, &D[i].e.x, &D[i].e.y);
			D[i].type = SEGMENT;
		}
		
		LINE2D wall1, wall2;
		wall1.type = wall2.type = LINE;
		wall1.s.x = wall1.e.x = 0;
		wall1.s.y = 1, wall1.e.y = 0;
		
		wall2.s.x = wall2.e.x = L;
		wall2.s.y = 1, wall2.e.y = 0;
		
		double r = L;
		for(int i = 0; i < n; i++) {
			if(i&1)
				r = min(r, closest(wall1, D[i]));
			else
				r = min(r, closest(wall2, D[i]));
			if(i + 1 < n) {
				r = min(r, closest(D[i], D[i+1]));
			}
		}
		printf("%.2lf\n", r);
	}
	return 0;
}
