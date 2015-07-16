#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
};
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
Pt getIntersect(Pt l1, Pt p1, Pt l2, Pt p2) {
	double a1, b1, c1, a2, b2, c2;
	double dx, dy, d;
	a1 = l1.y, b1 = -l1.x;
	c1 = a1 * p1.x + b1 * p1.y;
	a2 = l2.y, b2 = -l2.x;
	c2 = a2 * p2.x + b2 * p2.y;
	dx = c1 * b2 - c2 * b1, dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
	return Pt(dx/d, dy/d);
}
struct seg {
	Pt s, e;
	int label;
	seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
};

struct CMP {
	static double cos, sin;
	static Pt base;
    
	double interpolate(const Pt& p1, const Pt& p2) {
		double a1, a2, b1, b2, c1, c2, dx, dy, d, x, y;
		a1 = p1.y - p2.y, b1 = -(p1.x - p2.x), c1 = p1.x * a1 + p1.y * b1;
		a2 = sin, b2 = -cos, c2 = base.x * a2 + base.y * b2;
		dx = c1 * b2 - c2 * b1,	dy = a1 * c2 - a2 * c1;
		d = a1 * b2 - a2 * b1;
		x = dx / d, y = dy / d;
		return (base.x - x) * (base.x - x) + (base.y - y) * (base.y - y);
    }
	bool operator()(const seg &i, const seg &j) {
		double v1 = interpolate(i.s, i.e);
		double v2 = interpolate(j.s, j.e);
		if (fabs(v1 - v2) > eps)	return v1 < v2;
		return false;
	}
};
struct CMP2 {
	bool operator()(const double &i, const double &j) {
		if (fabs(i-j) > eps)
			return i < j;
		return false;
	}
};
double CMP::sin = 0, CMP::cos = 0;
Pt CMP::base = Pt();
const double pi = acos(-1);
int main() {	
	int n;
	double sx, sy, ex, ey;
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
	while (scanf("%d", &n) == 1) {
		int visual[32767] = {};
		seg D[32767];
		Pt pos = Pt(0, 0);
		set<seg, CMP> S;
		map<double, vector< pair<int, int> >, CMP2> angle;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
			D[i] = seg(Pt(sx, sy), Pt(ex, ey));
			D[i].label = i;
		}
		for (int i = 0; i < n; i++) {
			double v1 = atan2(D[i].s.y - pos.y, D[i].s.x - pos.x);
			double v2 = atan2(D[i].e.y - pos.y, D[i].e.x - pos.x);
			angle[v1].push_back(make_pair(i, 0));
			angle[v2].push_back(make_pair(i, 1));
		}
		double c;

		double ftheta = angle.begin()->first;
		pair<int, int> u = angle.begin()->second[0];
		Pt fpt;		
		CMP::base = pos;
		CMP::sin = sin(ftheta);
		CMP::cos = cos(ftheta);
		if (u.second == 0)
			fpt = D[u.first].s;
		else
			fpt = D[u.first].e;
		for (int i = 0; i < n; i++) {
			if (cross(pos, fpt, D[i].s) * cross(pos, fpt, D[i].e) < 0) {
				Pt q = getIntersect(D[i].s - D[i].e, D[i].s, fpt - pos, pos);
				if (dot(q - pos, fpt - pos) > 0)
					S.insert(D[i]);
			} 
		}
		for (map<double, vector< pair<int, int> >, CMP2>::iterator it = angle.begin();
			it != angle.end(); it++) {
			CMP::sin = sin(it->first);
			CMP::cos = cos(it->first);
			for (int i = 0; i < it->second.size(); i++) {
				pair<int, int> u = it->second[i];
				if (u.second == 0)
					c = cross(pos, D[u.first].s, D[u.first].e);
				else
					c = cross(pos, D[u.first].e, D[u.first].s);
				if (fabs(c) > eps) {
					if (c > 0)
						S.insert(D[u.first]);
					else
						S.erase(D[u.first]);
				}
			}
			if (S.size() > 0) {
				visual[S.begin()->label] = 1;
			}
		} 
		for (int i = 0; i < n; i++)
			printf("%d%s", visual[i], i == n-1 ? "" : " ");
		puts("");
	}
	return 0;
}
/*
1
5 -5 5 5

4
4 2 5 -2
2 4 6 1
5 5 8 1
3 -4 7 -1

7
-1 2 3 1
2 4 5 -1
-3 -1 1 -2
-1 -4 3 -2
-2 -4 1 -5
-4 1 -1 4
-3 4 -4 3

1
1 1 2 2

2
-1 3 -2 -2
-2 -1 -3 -1 
 
10
8 24 10 22
5 -4 3 -5
-1 -8 1 -6
1 2 -2 2
16 9 18 12
-15 -20 -18 -22
5 -19 0 -21
-17 -6 -15 -7
15 2 16 4
20 4 21 7

10
18 11 19 7
23 3 21 -2
-13 3 -11 -2
20 -12 23 -16
-13 2 -18 -3
15 14 10 16
-25 -2 -22 2
-6 14 -5 16
10 20 14 19
-19 5 -24 2
*/

