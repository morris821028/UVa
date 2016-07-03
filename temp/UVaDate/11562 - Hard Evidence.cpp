#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <assert.h>
#include <queue>
#include <algorithm>
using namespace std;
#define eps 1e-6
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
        // angle = atan2(e.y - s.y, e.x - s.x);
    }
    bool operator<(const Seg &other) const {
        if (fabs(angle - other.angle) > eps)
            return angle > other.angle;
        if (cross(other.s, other.e, s) > -eps)
            return true;
        return false;
    }
    bool operator!=(const Seg &other) const {
        return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
    }
};
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
    return acos(dot(va, vb) / va.length() / vb.length());
}
double distSeg2Point(Pt a, Pt b, Pt p) {
    Pt c, vab;
    vab = a - b;
    if (between(a, b, p)) {
        c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
        return (p - c).length();
    }
    return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
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
int cmpZero(double x) {
    if (fabs(x) < eps)  return 0;
    return x < 0 ? -1 : 1;
}
Pt projectLine(Pt as, Pt ae, Pt p) {
    double a, b, c, v;
    a = as.y - ae.y, b = ae.x - as.x;
    c = - (a * as.x + b * as.y);
    v = a * p.x + b * p.y + c;
    return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}
const double pi = acos(-1);

// this problem
void tangent_line(Pt p, Pt o, double r, Pt &b1, Pt &b2) { // p not in circle
    if (cmpZero((p - o).length() - r) == 0) {
        Pt vpo = p - o;
        b1 = p + Pt(-vpo.y, vpo.x);
        b2 = p + Pt(vpo.y, -vpo.x);
        return ;
    }
    double a, b, c, d; // (a, b), (c, d)
    double ma, mb, mc, sq;
    a = p.x, b = p.y, c = o.x, d = o.y;
    ma = (c-a)*(c-a) - r*r, mb = 2*(c-a)*(b-d), mc = (b-d)*(b-d) - r*r;
    sq = sqrt(mb*mb - 4*ma*mc);
//    printf("sq %lf %lf\n", sq, mb*mb - 4*ma*mc);
    if (cmpZero(ma) == 0) {
        b1 = p + Pt(1, -mc / mb);
        b2 = p + Pt(0, 1);
    } else if (cmpZero(sq) > 0) {
        b1 = p + Pt(1, (-mb + sq)/ 2 / ma);
        b2 = p + Pt(1, (-mb - sq)/ 2 / ma);
    } else {
        assert(false);
    }
}

vector<Pt> circleInterectLine(Pt a, Pt b, double r) { // maybe return same point
	vector<Pt> ret;
	Pt c, vab, p;
	double v, lab;
	c = projectLine(a, b, Pt(0, 0));
	if (cmpZero(c.length() - r) >= 0)
		return ret;
	vab = a - b, lab = (a - b).length();
	v = sqrt(r * r - (c.x * c.x + c.y * c.y));
	vab = vab * (v / lab);
	ret.push_back(c + vab);
	ret.push_back(c - vab);
	return ret;
}
const int MAXN = 256;
Pt D[MAXN];

double computeOpenAngle(Pt p, Pt D[], int N) {
	Pt l = D[0], r = D[0];
	for (int i = 1; i < N; i++) {
		if (cmpZero(cross(p, l, D[i])) < 0 && cmpZero(cross(p, r, D[i])) < 0)
			l = D[i];
		if (cmpZero(cross(p, l, D[i])) > 0 && cmpZero(cross(p, r, D[i])) > 0)
			r = D[i];
	}
	double ret = getAngle(r - p, l - p);
	return ret;
}
int main() {
    double R;
    int N, cases = 0;
    while (scanf("%d %lf", &N, &R) == 2) {
    	for (int i = 0; i < N; i++)
    		D[i].read();
    	
    	Pt o(0, 0);
    	vector< pair<double, Pt> > A;
    	for (int i = 0, j = N-1; i < N; j = i++) {
    		vector<Pt> c = circleInterectLine(D[i], D[j], R);
    		for (int j = 0; j < c.size(); j++) {
    			A.push_back(make_pair(atan2(c[j].y, c[j].x), c[j]));
    		}
    	}
    	
    	sort(A.begin(), A.end());
    	

    	double ret = 0;
    	
    	for (int i = 0; i < A.size(); i++) {
    		double l, r, mid, midmid, md, mmd;
    		l = A[i].first;
    		r = A[(i+1)%A.size()].first;
    		if (r < l)	r = r + 2*pi;
    		for (int it = 0; it < 15; it++) {
    			mid = (l + r)/2;
    			midmid = (mid + r)/2;
    			md = computeOpenAngle(Pt(R*cos(mid), R*sin(mid)), D, N);
    			mmd = computeOpenAngle(Pt(R*cos(midmid), R*sin(midmid)), D, N);
    			ret = max(ret, md), ret = max(ret, mmd);
    			if (md > mmd)
    				r = midmid;
    			else
    				l = mid;
    		}
    	}
    	
    	printf("%.10lf\n", ret);
    }
    return 0;
}

/*
4 2
-1.0 -1.0
1.0 -1.0
1.0 1.0
-1.0 1.0

3 2 
0 0 
1 0 
0 1
*/
