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
vector<Pt> circleInterectSeg(Pt a, Pt b, double r) {
	vector<Pt> ret;
	Pt c, vab, p;
	double v, lab;
	c = projectLine(a, b, Pt(0, 0));
	vab = a - b, lab = (a - b).length();
	if (cmpZero(c.x * c.x + c.y * c.y - r * r) > 0)
		return ret;
	v = sqrt(r * r - (c.x * c.x + c.y * c.y));
	vab = vab * (v / lab);
	p = c + vab;
	if (onSeg(a, b, p))
		ret.push_back(p);
	p = c - vab;
	if (onSeg(a, b, p))
		ret.push_back(p);
	if (ret.size() == 2 && ret[0] == ret[1])
		ret.pop_back();
	return ret;
}

bool cmp(pair<double, Pt> a, pair<double, Pt> b) {
    return a.first < b.first;
}
bool cmp2(pair<double, Seg> a, pair<double, Seg> b) {
    return a.first < b.first;
}
double scan(vector<Pt> poly, double r) {
	int n = poly.size();
	vector<Pt> all;
	
	for (int i = 0, j = n-1; i < n; j = i++) {
		all.push_back(poly[i]);
		all.push_back(poly[j]);
		vector<Pt> inter = circleInterectSeg(poly[i], poly[j], r);
		for (int k = 0; k < inter.size(); k++)
			all.push_back(inter[k]);
	}
	sort(all.begin(), all.end());
	all.resize(unique(all.begin(), all.end()) - all.begin());
	
    vector< pair<double, Pt> > polar;
    for (int i = 0; i < all.size(); i++) {
        Pt p = all[i];
        polar.push_back(make_pair(atan2(p.y, p.x), p));
    }
	sort(polar.begin(), polar.end(), cmp);
	
	double ret = 0;
	
	for (int i = 0; i < polar.size(); ) {
		vector<Pt> A, B;
		int idx1, idx2;
		double ltheta, rtheta;
		idx1 = i, ltheta = polar[i].first;
		while (idx1 < polar.size() && cmpZero(polar[i].first - polar[idx1].first) == 0)
			A.push_back(polar[idx1].second), idx1++;
		if (idx1 == polar.size()) // end
			break;
		idx2 = idx1, rtheta = polar[idx1].first;
		while (idx2 < polar.size() && cmpZero(polar[idx1].first - polar[idx2].first) == 0)
			B.push_back(polar[idx2].second), idx2++;
		i = idx1;
		
		if (A.size() == 0 || B.size() == 0)
			assert(false);
		
		for (int j = 0, k = n-1; j < n; k = j++) {
			if (cmpZero(cross(Pt(0, 0), A[0], poly[j])) * cmpZero(cross(Pt(0, 0), A[0], poly[k])) < 0)
				A.push_back(getIntersect(Seg(Pt(0, 0), A[0]), Seg(poly[j], poly[k])));
			if (cmpZero(cross(Pt(0, 0), B[0], poly[j])) * cmpZero(cross(Pt(0, 0), B[0], poly[k])) < 0)
				B.push_back(getIntersect(Seg(Pt(0, 0), B[0]), Seg(poly[j], poly[k])));
		}
		
		A.push_back(Pt(0, 0));
		B.push_back(Pt(0, 0));
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		A.resize(unique(A.begin(), A.end()) - A.begin());
		B.resize(unique(B.begin(), B.end()) - B.begin());
		
		vector< pair<double, Seg> > crossEdge;
		for (int p = 0; p < A.size(); p++) {
			for (int q = 0; q < B.size(); q++) {
				if (A[p] == B[q] || A[p] == Pt(0, 0) || B[q] == Pt(0, 0))
					continue;
				for (int j = 0, k = n-1; j < n; k = j++) {
					if (onSeg(poly[j], poly[k], A[p]) && onSeg(poly[j], poly[k], B[q])) {
						Pt mid = (A[p] + B[q]) * 0.5;
						crossEdge.push_back(make_pair((mid - Pt(0, 0)).length(), Seg(A[p], B[q])));
					}
				}
			}
		}
		crossEdge.push_back(make_pair(0.0, Seg(Pt(0, 0), Pt(0, 0))));
		sort(crossEdge.begin(), crossEdge.end(), cmp2);
		for (int j = 0; j < crossEdge.size() - 1; j++) {
			Seg a = crossEdge[j].second;
			Seg b = crossEdge[j+1].second;
			Pt ma = (a.s + a.e) * 0.5;
			Pt mb = (b.s + b.e) * 0.5;
			Pt mab = (ma + mb) * 0.5;
			if (!inPolygon(poly, mab))
				continue;
			double area = (fabs(cross(b.s, b.e, a.e)) + fabs(cross(a.s, a.e, b.s))) /2;
			
			int inout[4] = {}, all_in, all_out;
			inout[0] = cmpZero((a.s - Pt(0, 0)).length() - r) <= 0;
			inout[1] = cmpZero((a.e - Pt(0, 0)).length() - r) <= 0;
			inout[2] = cmpZero((b.s - Pt(0, 0)).length() - r) <= 0;
			inout[3] = cmpZero((b.e - Pt(0, 0)).length() - r) <= 0;
			all_in = inout[0] & inout[1] & inout[2] & inout[3];
			all_out = (!inout[0]) & (!inout[1]) & (!inout[2]) & (!inout[3]);			
//			printf("area %lf\n", area);
//			printf("%lf %lf, %lf %lf\n", a.s.x, a.s.y, a.e.x, a.e.y);
//			printf("%lf %lf, %lf %lf\n", b.s.x, b.s.y, b.e.x, b.e.y);
			if (all_out) {
//				printf("no %lf\n", 0);
				continue;
			}
			if (all_in) {
//				printf("all %lf\n", area);
				ret += area;
				continue;
			}
			if (inout[0] == 1 && inout[1] == 1) {
//				printf("part %lf\n", r * r * (rtheta - ltheta)/2 - fabs(cross(Pt(0, 0), a.s, a.e)) /2);
				ret += r * r * (rtheta - ltheta)/2 - fabs(cross(Pt(0, 0), a.s, a.e)) /2;
			} else {
//				printf("no %lf\n", 0);
			}
		}
//		puts("---");
	}
	
	return ret;
}
int main() {
	int n;
	double r, x, y;
	while (scanf("%d %lf", &n, &r) == 2) {
		vector<Pt> poly;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			poly.push_back(Pt(x, y));
		}
		
		double ret = scan(poly, r);
		printf("%.9lf\n", ret);
	}
	return 0;
}
/*
6 10
-8 2
8 2
8 14
0 14
0 6
-8 14

4 10
10 0
10 10
-10 10
-10 0

6 10
2 2
12 2
6 4
12 4
8 8
-2 8

5 10
-4 6
-2 2
0 4
4 2
8 4
*/

