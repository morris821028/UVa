#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>

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
double dist2Seg(Pt sa, Pt sb, Pt p) {
    double c = 1e+30;
    if(between(sa, sb, p))
        c = min(c, distProjection(sa, sb, p));
    else
        c = min(c, min(dist(sa, p), dist(sb, p)));
    return c;
}
int main() {
    int testcase;
    int n, m;
    Pt Di[128], Do[128];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &Di[i].x, &Di[i].y);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d %d", &Do[i].x, &Do[i].y);
        
        double ret = 1e+30;
        Di[n] = Di[0], Do[m] = Do[0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ret = min(ret, dist2Seg(Di[i], Di[i+1], Do[j]));
                ret = min(ret, dist2Seg(Do[j], Do[j+1], Di[i]));
            }
        }
        printf("%.8lf\n", ret/2);
    }
    return 0;
}

/*
 2
 4
 -5 -5
 5 -5
 5 5
 -5 5
 4
 -10 -10
 -10 10
 10 10
 10 -10
 3
 0 0
 1 0
 1 1
 5
 3 -3
 3 3
 -4 2
 -1 -1
 -2 -2
 */