#include <stdio.h>
#include <stdio.h>
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
double distProjection(Pt as, Pt at, Pt s) {
	double a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
struct Seg {
    Pt s, e;
};
int calcIntersection(Seg a, Seg b, Pt &p) {
    double a1, b1, c1, a2, b2, c2;
    double d, dx, dy;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x;
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    d = a1*b2 - a2*b1;
    dx = c1*b2 - c2*b1;
    dy = a1*c2 - a2*c1;
    if(fabs(d) < eps) // NONE or LINE
        return 0;
    p.x = dx / d, p.y = dy / d;
    /*printf("%lf %lf - %lf %lf\n", a.s.x, a.s.y, a.e.x, a.e.y);
    printf("%lf %lf - %lf %lf\n", b.s.x, b.s.y, b.e.x, b.e.y);
    printf("%lf %lf\n", p.x, p.y);*/
    return onSeg(a.s, a.e, p) && onSeg(b.s, b.e, p);
}
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}
double calcArea(Pt p[], int n) {
    if(n < 3)   return 0.0;
    double ret = 0;
    int i;
    p[n] = p[0];
    for(i = 0; i < n; i++)
        ret += p[i].x * p[i+1].y - p[i].y * p[i+1].x;
    return fabs(ret)/2;
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}

#define INF 1e+30 
// ternary search
double calcSquare(double m, Pt p, Pt ch[], int n) {
	double a, b, c, lab;
	double w = 0, hl = 0, hr = 0, h;
	a = sin(m), b = -cos(m), c = - (a * p.x + b * p.y), lab = hypot(a, b);
	
	int pp = 0, qq = 0;
	for(int i = 0; i < n; i++) {
		double d = fabs(a * ch[i].x + b * ch[i].y + c) / lab;
		w = max(w, d);
		if(a * ch[i].x + b * ch[i].y + c < - 1e-6)
			pp++;
		if(a * ch[i].x + b * ch[i].y + c > 1e-6)
			qq++;
	}
//	printf("%d %d\n", pp, qq);
	a = cos(m), b = sin(m), c = - (a * p.x + b * p.y), lab = hypot(a, b);
	for(int i = 0; i < n; i++) {
		double d = fabs(a * ch[i].x + b * ch[i].y + c) / lab;
		if(a * ch[i].x + b * ch[i].y + c < 0)
			hl = max(hl, d);
		else
			hr = max(hr, d);
	}
	h = hl + hr;
	return max(w, h) * max(w, h);
}
const double pi = acos(-1);
double ternary_search(double l, double r, Pt p, Pt ch[], int n) {
	double mid, midmid, md, mmd;
	double ret = INF;
	while(fabs(l-r) > eps) {
		mid = (l+r)/2;
		midmid = (mid+r)/2;
		md = calcSquare(mid, p, ch, n);
		mmd = calcSquare(midmid, p, ch, n);
		ret = min(ret, md);
		ret = min(ret, mmd);
		if(md < mmd)
			r = midmid;
		else
			l = mid;
	}
//	printf("best %lf %lf\n", l / pi * 180, ret);
	return ret;
}
double smallSquare(int n, Pt ch[]) {
	double ret = INF;
	
	for(int i = 0, j = n-1; i < n; j = i++) {
//		printf("pt[%lf %lf]\n", ch[i].x, ch[i].y);
		double l = atan2(ch[j].y - ch[i].y, ch[j].x - ch[i].x);
		double r = atan2(ch[(i+1)].y - ch[i].y, ch[(i+1)].x - ch[i].x) - pi;
//		printf("l r [%lf %lf]\n", l, r);
		r = l + fmod(fmod(r - l, 2 * pi) + 2 * pi, 2 * pi);
		if(l <= r) {
			ret = min(ret, ternary_search(l, r, ch[i], ch, n));
		} else {
			ret = min(ret, ternary_search(l, pi, ch[i], ch, n));
			ret = min(ret, ternary_search(-pi, r, ch[i], ch, n));
		}
	}
	return ret;
}
int main() {
    Pt p[2048], ch[2048];
    int n, m;
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d", &n);
    	for(int i = 0; i < n; i++)
    		scanf("%lf %lf", &p[i].x, &p[i].y);
        m = monotone(n, p, ch);
//        for(int i = 0; i < m; i++)
//        	printf("%lf %lf\n", ch[i].x, ch[i].y);
    	
    	if(m == 1) {
    		printf("%.2lf\n", 0);
    		continue;
    	}
		double ret = smallSquare(m, ch);
		printf("%.2lf\n", ret);
    }
    return 0;
}
/*
5
4
10 1
10 -1
-10 1
-10 -1

2
4
-1 -1
1 -1
1 1
-1 1
4
10 1
10 -1
-10 1
-10 -1
*/
