#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>
#include <vector>
#include <string.h>
using namespace std;
#define eps 1e-9
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
	double length2() {
		return x*x + y*y;
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

// 
vector<Pt> circleInterectSeg(Pt a, Pt b, double r) { // maybe return same point
	vector<Pt> ret;
	Pt c, vab, p;
	double v, lab;
	c = projectLine(a, b, Pt(0, 0));
	if (cmpZero(c.length() - r) >= 0)
		return ret;
	vab = a - b, lab = (a - b).length();
	v = sqrt(r * r - (c.x * c.x + c.y * c.y));
	vab = vab * (v / lab);
	if (onSeg(a, b, c + vab))
		ret.push_back(c + vab);
	if (onSeg(a, b, c - vab))
		ret.push_back(c - vab);
	return ret;
}
double circleWithTriangle(double r, Pt a, Pt b) { // get intersect area
	Pt o = Pt(0, 0);
	double la = (a - Pt(0, 0)).length();
	double lb = (b - Pt(0, 0)).length();
	
	if (cmpZero(cross(o, a, b)) == 0)
		return 0;
	
	if (cmpZero(la - r) <= 0 && cmpZero(lb - r) <= 0)
		return fabs(cross(o, a, b))/2;
	
	if (cmpZero(la - r) <= 0 || cmpZero(lb - r) <= 0) {
		if (cmpZero(la - r) > 0)
			swap(a, b), swap(la, lb);
		// a in circle, b not in circle
		vector<Pt> c = circleInterectSeg(a, b, r);
		assert(c.size() > 0);
		
		if (c.size() > 1 && c[0] == a)
			swap(c[0], c[1]);
		double theta = getAngle(c[0], b);
		double ret = 0;
		
		ret += fabs(cross(o, a, c[0]))/2;
		ret += r * r * theta/2;
		
		return ret;
	}
	// a not in circle, b not in circle
	vector<Pt> c = circleInterectSeg(a, b, r);
	if (c.size() == 0) {
		double theta = getAngle(a, b);
		return r * r * theta/2;
	} else {
		assert(c.size() == 2);
		if (dot(c[0] - a, b - a) > dot(c[1] - a, b - a))
			swap(c[0], c[1]);
		double theta1 = getAngle(a, c[0]);
		double theta2 = getAngle(c[1], b);
		double ret = 0;
		
		ret += r * r * (theta1+theta2)/2;
		ret += fabs(cross(o, c[0], c[1]))/2;
		return ret;
	}
	return 0;
}

void circleInterectLine(Pt c, double r, Pt s, Pt e, Pt &r1, Pt &r2) {
	Pt p = c + Pt(e.y - s.y, s.x - e.x);
	p = getIntersect(Seg(p, c), Seg(s, e));
	double d = (p - c).length();
	double t = sqrt(r*r - d*d) / (s - e).length();
	r1 = p + (s - e) * t;
	r2 = p - (s - e) * t;
}
int rayToCircle(Pt s, Pt e, Pt c, double r, Pt &pt) {
	Pt a = projectLine(s, e, c);
	if (cmpZero((a - c).length() - r) >= 0)
		return 0;
	Pt p1, p2;
	circleInterectLine(c, r, s, e, p1, p2);
	
	if (cmpZero(dot(e - s, p1 - s)) <= 0)
		return 0;
	if (cmpZero(dot(e - s, p2 - s)) <= 0)
		return 0;
	pt = (p1 - s).length() < (p2 - s).length() ? p1 : p2;
	return 1;
}
int main() {
	int cases = 0;
	int n;
	const int MAXN = 32;
	
	Pt cp[MAXN], base, dir;
	double cr[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf %lf", &cp[i].x, &cp[i].y, &cr[i]);
		scanf("%lf %lf %lf %lf", &base.x, &base.y, &dir.x, &dir.y);
		
		printf("Scene %d\n", ++cases);
		
		vector<int> ret;
		int prev_id = -1;
		for (int it = 0; it <= 10; it++) {
			int next_id = -1;
			Pt far = base + dir;
			for (int i = 0; i < n; i++) {
				if (i == prev_id)
					continue;
				Pt tmp;
				if (rayToCircle(base, far, cp[i], cr[i], tmp)) {
					if (next_id == -1 || (far - base).length2() > (tmp - base).length2()) {
						far = tmp, next_id = i;
					}
				}
			}
			
			if (next_id < 0) {
				ret.push_back(-1);
				break;
			}
			ret.push_back(next_id);
			Pt a, b;
			a = projectLine(cp[next_id], far, base);
			b = base + (a - base) * 2;
			base = far;
			dir = b - base;
			prev_id = next_id;
		}
		for (int i = 0; i < ret.size() && i <= 10; i++) {
			if (ret[i] == -1)
				printf("inf");
			else if (i == 10)
				printf("...");
			else
				printf("%d", ret[i]+1);
			printf("%c", i == ret.size()-1 ? '\n' : ' ');
		}
		puts("");
	}
	return 0;
}
/*
1
0 0 1
1 2 0 -1
2
0 0 1
1 -2 1
1 2 0 -1
3
0 0 1
1 -2 1
1 3 1
1 2 0 -1
3
0 0 1
1 -3 1
1 3 1
1 2 0 -1
10
0 0 1
1 3 1
2 0 1
3 3 1
4 0 1
5 3 1
6 0 1
7 3 1
8 0 1
9 3 1
-1 2 1 -1
11
0 0 1
1 3 1
2 0 1
3 3 1
4 0 1
5 3 1
6 0 1
7 3 1
8 0 1
9 3 1
10 0 1
-1 2 1 -1
3
3 3 2
7 7 1
8 1 1
3 8 1 -4
2
0 0 1
5 0 2
2 0 1 0
0
*/

