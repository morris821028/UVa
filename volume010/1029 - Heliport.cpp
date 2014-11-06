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
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(onSeg(q, p[i], p[j]))
            return 1;
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}
// this problem
Pt D[1024];
int N;
int checkCircle(double x, double y, double r) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (D[i].x > x && (D[i].y > y != D[i+1].y > y))
			cnt++;
	}
	if (cnt%2 == 0)	return 0;
	for (int i = 0; i < N; i++) {
		if ((D[i].x - x) * (D[i].x - x) + (D[i].y - y) * (D[i].y - y) < (r - eps)* (r - eps))
			return 0;
		if (D[i].x == D[i + 1].x && (D[i].y > y != D[i+1].y > y) && fabs(D[i].x - x) < r - eps)
			return 0;
		if (D[i].y == D[i + 1].y && (D[i].x > x != D[i+1].x > x) && fabs(D[i].y - y) < r - eps)
			return 0;
	}
	return 1;
}
int checkRadius(double r) {
	for (int i = 0; i < N; i++) {
		if (D[i].x == D[i+1].x)
		for (int j = 0; j < N; j++) {
			if (D[j].y == D[j+1].y) {
				if (checkCircle(D[i].x + r, D[j].y + r, r))
					return 1;
				if (checkCircle(D[i].x + r, D[j].y - r, r))
					return 1;
				if (checkCircle(D[i].x - r, D[j].y + r, r))
					return 1;
				if (checkCircle(D[i].x - r, D[j].y - r, r))
					return 1;
			}
		}
	}
	
	double d, dd, dx, dy, x, y;
	for (int i = 0; i < N; i++) { // (line, point) => circle
		for (int j = 0; j < N; j++) {
			if (D[i].x == D[i+1].x) {
				d = fabs(D[j].x - (D[i].x + r));
				if (d < r) {
					dy = sqrt(r*r - d*d);
					if (checkCircle(D[i].x + r, D[j].y + dy, r))
						return 1;
					if (checkCircle(D[i].x + r, D[j].y - dy, r))
						return 1;
				}
				d = fabs(D[j].x - (D[i].x - r));
				if (d < r) {
					dy = sqrt(r*r - d*d);
					if (checkCircle(D[i].x - r, D[j].y + dy, r))
						return 1;
					if (checkCircle(D[i].x - r, D[j].y - dy, r))
						return 1;
				}
			} else {
				d = fabs(D[j].y - (D[i].y + r));
				if (d < r) {
					dx = sqrt(r*r - d*d);
					if (checkCircle(D[j].x + dx, D[i].y + r, r))
						return 1;
					if (checkCircle(D[j].x - dx, D[i].y + r, r))
						return 1;
				}
				d = fabs(D[j].y - (D[i].y - r));
				if (d < r) {
					dx = sqrt(r*r - d*d);
					if (checkCircle(D[j].x + dx, D[i].y - r, r))
						return 1;
					if (checkCircle(D[j].x - dx, D[i].y - r, r))
						return 1;
				}
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			x = (D[i].x + D[j].x)/2;
			y = (D[i].y + D[j].y)/2;
			d = hypot(x - D[i].x, y - D[i].y);
			if (d < r) {
				dd = sqrt(r*r - d*d);
				dx = (y - D[i].y)/d * dd;
				dy = (D[i].x - x)/d * dd;
				
				if (checkCircle(x + dx, y + dy, r))
					return 1;
				if (checkCircle(x - dx, y - dy, r))
					return 1;
			}
		}
	}
	return 0;
}
int main() {
	int n, x, cases = 0;
	char cmd[1024];
    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};
    int R[128];
    R['R'] = 0, R['U'] = 1, R['L'] = 2, R['D'] = 3;
    while(scanf("%d", &n) == 1 && n) {
    	D[0] = Pt(0, 0), N = n;
    	for (int i = 1; i <= n; i++) {
    		scanf("%d %s", &x, cmd);
    		D[i].x = D[i-1].x + x * dx[R[cmd[0]]];
    		D[i].y = D[i-1].y + x * dy[R[cmd[0]]];
    	}
    	double l = 0, r = 1000, ret, mid;
    	while (fabs(l - r) > eps) {
    		mid = (l + r)/2;
    		if (checkRadius(mid))
    			l = mid, ret = mid;
    		else
    			r = mid;
    	}
    	if (cases)	puts("");
    	printf("Case Number %d radius is: %.2lf\n", ++cases, ret);
    }
    return 0;
}
/*
4
2 R 2 U 2 L 2 D
10
10 R 10 U 10 L 10 U 10 R 5 U 30 L 20 D 20 R 5 D
12
1 R 1 U 1 R 1 U 1 L 1 U
1 L 1 D 1 L 1 D 1 R 1 D
 */
