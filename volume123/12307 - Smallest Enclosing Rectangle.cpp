// Accepted
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
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
void smallRect(int n, Pt p[]) {
	int l = 1, r = 1, u = 1;
    double area = INF, per = INF;
	for( int i = 0; i < n; i++) {
		Pt edge = (p[(i+1)%n]-p[i]) / dist(p[(i+1)%n], p[i]);
        
		while(dot(edge, p[r%n]-p[i]) < dot(edge, p[(r+1)%n]-p[i]))
            r++;
		while(u < r || cross2(edge, p[u%n]-p[i]) < cross2(edge, p[(u+1)%n]-p[i]))
            u++;
		while(l < u || dot(edge, p[l%n]-p[i]) > dot(edge, p[(l+1)%n]-p[i]))
            l++;

		double w = dot(edge, p[r%n]-p[i]) - dot(edge, p[l%n]-p[i]);
		double h = fabs(cross2(p[i]-p[u%n], p[(i+1)%n]-p[u%n]) / dist(p[i], p[(i+1)%n]));
        
		area = min(area, w * h);
		per = min(per, (w + h)*2);
	}
    printf("%.2lf %.2lf\n", area, per);
}
Pt p[262144], ch[262144];
int main() {
    int n, m;
    while(scanf("%d", &n) == 1 && n) {
    	for(int i = 0; i < n; i++)
    		scanf("%lf %lf", &p[i].x, &p[i].y);
        m = monotone(n, p, ch);
		smallRect(m, ch);
    }
    return 0;
}

/*
 5
 0 0
 2 0
 2 2
 0 2
 1 1
 5
 1 1
 9 0
 7 10
 0 5
 2 11
 3
 5 3
 7 2
 6 6
 4
 6 3
 9 1
 9 6
 8 10
 0
 */
