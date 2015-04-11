// Euler characteristic, V - E + F = 2
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
// maybe collinear !!!!!!!!
int main() {
	const int MAXN = 305;
	int n, cases = 0;
	Pt D[MAXN];
	while (scanf("%d", &n) == 1 && n) {		
		int V = 0, E = 0; 
		vector<Pt> SV;
		
		for (int i = 0; i < n; i++)
			D[i].read(), SV.push_back(D[i]);

		for (int i = 0; i+1 < n; i++) {
			for (int j = i+1; j+1 < n; j++) {
				if (intersection(D[i], D[i+1], D[j], D[j+1])) {
					Pt p = getIntersect(Seg(D[i], D[i+1]), Seg(D[j], D[j+1]));
					SV.push_back(p);
				}
			}
		}
		
		sort(SV.begin(), SV.end());
		SV.resize(unique(SV.begin(), SV.end()) - SV.begin());
		V = SV.size(), E = n - 1;
		for (int i = 0; i < SV.size(); i++) {
			for (int j = 0; j+1 < n; j++) {
				if (onSeg(D[j], D[j+1], SV[i]) && SV[i] != D[j] && SV[i] != D[j+1])
					E++;
			}
		}
//		printf("%d %d\n", E, V);
		int ret = E - V + 2; // V - E + F = 2, F = E - V + 2
		printf("Case %d: There are %d pieces.\n", ++cases, ret);
	}
	return 0;
}
/*
7 
1 1 1 5 2 1 2 5 5 1 3 5 1 1 
0
*/

