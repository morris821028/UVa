#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>
#include <vector>
#include <string.h>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Pt &a) const {
    	return !(a == *this);
	}
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	double length() {
		return hypot(x, y);
	}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
};
const double pi = acos(-1);
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
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
struct Seg {
	Pt s, e;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0): s(a), e(b), label(l) {
	}
	bool operator!=(const Seg &other) const {
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
	if (cmpZero(cross(as, at, bs) * cross(as, at, bt)) < 0 &&
		cmpZero(cross(bs, bt, as) * cross(bs, bt, at)) < 0)
		return 1;
	return 0;
}
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
	return acos(dot(va, vb) / va.length() / vb.length());
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}
int inPolygon(vector<Pt> &p, Pt q) {
	int i, j, cnt = 0;
	int n = p.size();
	for(i = 0, j = n-1; i < n; j = i++) {
		if(onSeg(p[i], p[j], q))
			return 1;
		if(p[i].y > q.y != p[j].y > q.y &&
		q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
		cnt++;
	}
	return cnt&1;
}
double polygonArea(vector<Pt> &p) {
    double area = 0;
    int n = p.size();
    for(int i = 0; i < n;i++)
		area += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1)%n].x;
    return fabs(area) /2;
}

Pt projectLine(Pt as, Pt ae, Pt p) {
	double a, b, c, v;
	a = as.y - ae.y, b = ae.x - as.x;
	c = - (a * as.x + b * as.y);
	v = a * p.x + b * p.y + c;
	return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}

int main() {
	int testcase, e[3];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &e[0], &e[1], &e[2]);
		sort(e, e+3);
		
		double sq_len = 0;
		
		if (e[0]*e[0] + e[1]*e[1] <= e[2]*e[2]) { // right/obtuse triangle
			double a = e[2], b = e[1], c = e[0]; // a > b > c
			double theta = acos((a*a + b*b - c*c)/(2*a*b));
			Pt A = rotateRadian(Pt(1, 0), theta) * b;
			Pt vAC = rotateRadian(Pt(0, 0) - A, pi/4), vAB = rotateRadian(Pt(a, 0) - A, -pi/4);
			Pt p = getIntersect(Seg(Pt(0, 0), Pt(a, 0)), Seg(A + vAC, A));
			Pt q = getIntersect(Seg(Pt(0, 0), Pt(a, 0)), Seg(A + vAB, A));
			sq_len = max((A - p).length(), (A - q).length()) / sqrt(2);	
		} else {
			double a = e[2], b = e[1], c = e[0]; // a > b > c
			double s = (a+b+c)/2;
			double area = sqrt(s*(s-a)*(s-b)*(s-c));
			double h = 2 * area / a;
			h = 2 * area / b;
			sq_len = max((b*h) / (b + h), sq_len);
			h = 2 * area / c;
			sq_len = max((c*h) / (c + h), sq_len);
		}
			double a = e[2], b = e[1], c = e[0]; // a > b > c
			double s = (a+b+c)/2;
			double area = sqrt(s*(s-a)*(s-b)*(s-c));
			double h = 2 * area / a;
			// h - x : h = x : a
			// x = ah / (h + a) 
			sq_len = max((a*h) / (a + h), sq_len);
	
		printf("%.6lf\n", sq_len * sq_len);
	}
	return 0;
}
/*

3
3 4 5
6 4 3
6 7 8

2
6 6 6
2 2 2
*/


