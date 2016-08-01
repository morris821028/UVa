#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define eps 1e-6
const double pi = acos(-1);
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
    void read() {
        scanf("%lf %lf", &x, &y);
    }
    void print() {
    	printf("%.0lf %.0lf\n", x, y);
    }
};
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
int cmpZero(double x) {
    if (fabs(x) < eps)	return 0;
    return x < 0 ? -1 : 1;
}

struct Seg {
    Pt s, e;
    Seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}   
};    
int intersect(Pt as, Pt at, Pt bs, Pt bt) {
    if (min(as.x, at.x) > max(bs.x, bt.x) ||
        min(as.y, at.y) > max(bs.y, bt.y) ||
        max(as.x, at.x) < min(bs.x, bt.x) ||
        max(as.y, at.y) < min(bs.y, bt.y))
        return 0;
        
    if(cmpZero(cross(as, at, bs)) * cmpZero(cross(as, at, bt)) < 0 &&
       cmpZero(cross(at, as, bs)) * cmpZero(cross(at, as, bt)) < 0 &&
       cmpZero(cross(bs, bt, as)) * cmpZero(cross(bs, bt, at)) < 0 &&
       cmpZero(cross(bt, bs, as)) * cmpZero(cross(bt, bs, at)) < 0)
        return 1;
    return 0;
}
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}

const int MAXN = 256;
double getH(double X, int N, Seg segs[]) {
	double mxY = 0;
	for (int i = 0; i < N; i++) {
		if (min(segs[i].s.x, segs[i].e.x) > X)
			continue;
		if (max(segs[i].s.x, segs[i].e.x) < X)
			continue;
		double y = segs[i].s.y + (segs[i].e.y - segs[i].s.y) * (X - segs[i].s.x) / (segs[i].e.x - segs[i].s.x);
		mxY = max(mxY, y);
	}
	return mxY;
}
int computeSkyline(int N, Seg segs[]) {
	vector<double> sweepline;
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {			
			if (intersect(segs[i].s, segs[i].e, segs[j].s, segs[j].e))
				sweepline.push_back(getIntersect(segs[i], segs[j]).x);
		}
		sweepline.push_back(segs[i].s.x);
		sweepline.push_back(segs[i].e.x);
	}
	
	sort(sweepline.begin(), sweepline.end());
	sweepline.resize(unique(sweepline.begin(), sweepline.end()) - sweepline.begin());
	double ret = 0;
	for (int i = 0; i+1 < sweepline.size(); i++) {		
		double lx = sweepline[i], rx = sweepline[i+1];
		double ly = getH(lx, N, segs), ry = getH(rx, N, segs);
		if (ly == ry && cmpZero(ly) == 0)
			continue;
		ret += hypot(lx - rx, ly - ry);
//		printf("[%lf %lf] %lf %lf\n", lx, rx, ly, ry);
	}
	return (int) round(ret);
}
int main() {
    int N, cases = 0;
    Seg segs[MAXN];
    while (scanf("%d", &N) == 1 && N) {
    	int M = 0;
    	for (int i = 0; i < N; i++) {
    		double X, H, B;
    		scanf("%lf %lf %lf", &X, &H, &B);
    		
    		double lx = X - B/2, rx = X + B/2;
    		segs[M++] = Seg(Pt(lx, 0), Pt(X, H));
    		segs[M++] = Seg(Pt(rx, 0), Pt(X, H));
    	}
    	printf("Case %d: %d\n", ++cases, computeSkyline(M, segs));
    	puts("");
    }
    return 0;
}
/*
1 
100 50 100 
2
100 50 100 
100 50 100 
3 
20 30 35 
37 24 29 
60 20 13
 */
