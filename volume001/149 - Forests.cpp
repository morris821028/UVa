#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
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
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator/(const double a) const {
        return Pt(x/a, y/a);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dist2(Pt a, Pt b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
double length(Pt a) {
	return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double angle(Pt a, Pt b) {
	return acos(dot(a, b) / length(a) / length(b));
}
Pt getLineIntersection(double a1, double b1, double c1, double a2, double b2, double c2) {
	// a1 x + b1 y + c1 = 0, a2 x + b2 y + c2 = 0
	c1 = -c1, c2 = -c2;
	double d, dx, dy;
	d = a1 * b2 - a2 * b1;
	dx = c1 * b2 - c2 * b1;
	dy = a1 * c2 - a2 * c1;
	return Pt(dx/d, dy/d);
}
void getTangentIntersection(Pt co, double r, Pt p, Pt &pa, Pt &pb) {
	double a, b, c;
	double m1a, m1b, m1c, m2a, m2b, m2c, m1, m2;
	a = r*r - (co.x - p.x) * (co.x - p.x);
	b = 2 * (co.x - p.x) * (co.y - p.y);
	c = r*r - (co.y - p.y) * (co.y - p.y); // am^2 + bm + c = 0
	if(fabs(a) < eps) {
		m2 = (-c)/b;
		m1a = 1, m1b = 0, m1c = - (m1a * p.x + m1b * p.y);
		m2a = m2, m2b = -1, m2c = - (m2a * p.x + m2b * p.y);
	} else {
		m1 = (-b + sqrt(b*b - 4*a*c))/ (2*a);
		m2 = (-b - sqrt(b*b - 4*a*c))/ (2*a);
		m1a = m1, m1b = -1, m1c = - (m1a * p.x + m1b * p.y);
		m2a = m2, m2b = -1, m2c = - (m2a * p.x + m2b * p.y);
	}
	pa = getLineIntersection(m1a, m1b, m1c, m1b, -m1a, -(m1b * co.x + (-m1a) * co.y));
	pb = getLineIntersection(m2a, m2b, m2c, m2b, -m2a, -(m2b * co.x + (-m2a) * co.y));
}
struct Interval {
	Pt p;
	double dist, l, r;
	Interval(double a = 0, double b = 0, double c = 0, Pt d = Pt()):
		dist(a), l(b), r(c), p(d) {
	}
	bool operator<(const Interval &x) const {
		return dist < x.dist;
	}
};
int main() {
	Pt pa, pb, co(1, 1), p(0, 0);
	const double pi = acos(-1);
	double diameter, radius;
	while(scanf("%lf %lf %lf", &diameter, &p.x, &p.y) == 3) {
		if(fabs(diameter) < eps)
			break;
		vector<Interval> interval;
		radius = diameter/2;
		for(int i = -20; i < 20; i++) {
			for(int j = -20; j < 20; j++) {
				getTangentIntersection(Pt(i, j), radius, p, pa, pb);
				double t1, t2;
				t1 = atan2(pa.y - p.y, pa.x - p.x);
				t2 = atan2(pb.y - p.y, pb.x - p.x);
				if(t1 > t2)	swap(t1, t2);
				if(fabs(t1 - t2)*180/pi < 0.01f)
					continue;
				interval.push_back(Interval(pow(pa.x-p.x, 2)+pow(pb.y-p.y, 2), t1, t2, Pt(i, j)));
			}
		}
		sort(interval.begin(), interval.end());
		int ret = 0;
		for(int i = 0; i < interval.size(); i++) {
			double t1 = interval[i].l, t2 = interval[i].r;
			if(t2 - t1 < pi) {
				int f = 1;
				for(int j = 0; j < i; j++) {
					double l = max(t1, interval[j].l), r = min(t2, interval[j].r);
					if(l <= r + 0.01f * pi/180)
						f = 0, j = i;
				}
				ret += f;
			} else {				
				double t3, t4;
				t3 = t2, t4 = pi;
				t2 = t1, t1 = -pi;
				int f = 1;
				for(int j = 0; j < i; j++) {
					double l = max(t1, interval[j].l), r = min(t2, interval[j].r);
					if(l <= r + 0.01f * pi/180)
						f = 0, j = i;
				}
				if(!f)
					continue;
				t1 = t3, t2 = t4;
				for(int j = 0; j < i; j++) {
					double l = max(t1, interval[j].l), r = min(t2, interval[j].r);
					if(l <= r + 0.01f * pi/180)
						f = 0, j = i;
				}
				if(!f)
					continue;
				ret += f;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
0.10 0.46 0.38
*/
