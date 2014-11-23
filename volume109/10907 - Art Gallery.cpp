#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-6
#define MAXN 131072
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
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	bool operator==(const Pt &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	} 
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
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
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
};
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
	if (onSeg(as, at, bs) || onSeg(as, at, bt) ||
		onSeg(bs, bt, as) || onSeg(bs, bt, at))
		return 1;
	if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
		cross(at, as, bs) * cross(at, as, bt) < 0 &&
		cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
		cross(bt, bs, as) * cross(bt, bs, at) < 0)
	return 1;
	return 0;
}
int inPolygon(Pt p[], int n, Pt q) {
	int i, j, cnt = 0;
	for(i = 0, j = n-1; i < n; j = i++) {
		if(onSeg(p[i], p[j], q))
			return 1;
		if(p[i].y > q.y != p[j].y > q.y &&
			q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
			cnt++;
	}
	return cnt&1;
}
const double pi = acos(-1);
double artGallery(Pt p[], int n, Pt q) { // polygon: anti-clockwise order
	vector< pair<double, Pt> > A;
	for (int i = 0; i < n; i++) {
		if (!(p[i] == q))
			A.push_back(make_pair(atan2(p[i].y - q.y, p[i].x - q.x), p[i]));
	}
	sort(A.begin(), A.end());
	double ret = 0;
	int m = A.size();
	for (int i = 0, j = m-1; i < m; j = i++) {
		if (fabs(A[i].first - A[j].first) > eps) {
			vector<Seg> segs;
			Pt a, b, ta, tb;
			a = q + (A[j].second - q) * 10000;
			b = q + (A[i].second - q) * 10000;
			for (int k = 0, l = n-1; k < n; l = k++) {
				if ((cross(q, A[j].second, p[k]) * cross(q, A[j].second, p[l]) < eps 
					&& cross(q, A[i].second, p[k]) * cross(q, A[i].second, p[l]) < eps)) {
					if (p[l] == q || p[k] == q)	continue;
					if (intersection(a, q, p[l], p[k]) && intersection(b, q, p[l], p[k]) && !onSeg(p[l], p[k], q))
						segs.push_back(Seg(p[l], p[k]));
				}
			}
//			printf("base %lf %lf %lf %lf\n", A[i].second.x, A[i].second.y, A[j].second.x, A[j].second.y);
			for (int i = 0; i < segs.size(); i++) {
//				printf("%lf %lf %lf %lf\n", segs[i].s.x, segs[i].s.y, segs[i].e.x, segs[i].e.y);
				if (intersection(a, q, segs[i].s, segs[i].e)) {
					ta = getIntersect(Seg(a, q), segs[i]);
					tb = getIntersect(Seg(b, q), segs[i]);
					if (dist(ta, q) < dist(a, q) && !(a == q))
						a = ta;
					if (dist(tb, q) < dist(b, q) && !(b == q))
						b = tb;
				}
			}
			if (inPolygon(p, n, Pt((a.x + b.x)/2, (a.y + b.y)/2)) &&
				inPolygon(p, n, Pt((a.x + q.x)/2, (a.y + q.y)/2)) &&
				inPolygon(p, n, Pt((q.x + b.x)/2, (q.y + b.y)/2))) {
				ret += fabs(cross(q, a, b))/2;
//				puts("Y");
			}
//			printf("---- %lf %lf %lf %lf\n", a.x, a.y, b.x, b.y);
//			puts("--");
		}
	}
	return ret;
}
int main() {
	int testcase, cases = 0;
	int n, m;
	double x, y;
	Pt D[105];
	while(scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &D[i].x, &D[i].y);
		scanf("%d", &m);
		printf("Gallery #%d\n", ++cases);
		for (int i = 0; i < m; i++) {
			scanf("%lf %lf", &x, &y);
			double area = artGallery(D, n, Pt(x, y));
			printf("%.2lf\n", area);
		}
	} 
	return 0;
}
/*
5
0 0
50 50
100 0
100 100
0 100
2
49 50
50 51

7
0 5
5 0
10 7
15 0
20 5
15 10
5 10
7
0 5
5 0
10 7
15 0
20 5
15 10
5 10

*/
