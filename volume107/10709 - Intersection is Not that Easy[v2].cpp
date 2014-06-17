#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define eps 1e-6
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
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
		int a1, a2, b1, b2, c1, c2;
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
		int a1, b1, c1;
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
	// freopen("in.txt", "r+t", stdin);
	// freopen("out.txt", "w+t", stdout); 
	int x1, x2, y1, y2;
	LINE2D l1, l2;
	char s[1024];
	while(scanf("%d %d %d %d %s", &x1, &y1, &x2, &y2, s) == 5 && s[0] != 'E') {
		l1.s = Pt(x1, y1), l1.e = Pt(x2, y2);
		if(!strcmp("L", s))
			l1.type = LINE;
		else
			l1.type = SEGMENT;
		scanf("%d %d %d %d %s", &x1, &y1, &x2, &y2, s);
		l2.s = Pt(x1, y1), l2.e = Pt(x2, y2);
		if(!strcmp("L", s))
			l2.type = LINE;
		else
			l2.type = SEGMENT;
		double ret = closest(l1, l2);
		printf("%.5lf\n", ret);
	}
	return 0;
}
/*
10 10 20 20 L
-10 -10 19 19 L

10 10 12 13 LS
11 11 19 20 LS

1 1 2 2 LS
3 3 4 4 LS

1 1 2 2 LS
3 3 4 4 L

10 10 12 12 END
11 11 23 34 END
*/
