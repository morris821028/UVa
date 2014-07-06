#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
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
double distToSeg(Pt sa, Pt sb, Pt a) {
	if(!(sa == sb) && between(sa, sb, a))
		return distProjection(sa, sb, a);
	return min(dist(sa, a), dist(sb, a));
}
int main() {
	int testcase, cases = 0, A, B;
	Pt DA[105], DB[105];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &A, &B);
		for(int i = 0; i < A; i++)
			scanf("%lf %lf", &DA[i].x, &DA[i].y);
		for(int i = 0; i < B; i++)
			scanf("%lf %lf", &DB[i].x, &DB[i].y);
		
		double alen = 0, blen = 0;
		for(int i = 1; i < A; i++)
			alen += dist(DA[i], DA[i-1]);
		for(int i = 1; i < B; i++)
			blen += dist(DB[i], DB[i-1]);
		
		int aIdx, bIdx;
		double sa, sb, run;
		Vector va, vb;
		Pt apos = DA[0], bpos = DB[0];
		aIdx = bIdx = 0;
		
		double mxDist = 0, mnDist = 1e+30;
		while(aIdx < A - 1 && bIdx < B - 1) {
			sa = dist(DA[aIdx+1], apos);
			sb = dist(DB[bIdx+1], bpos);
			run = min(sa/alen, sb/blen); // run time
			va = (DA[aIdx+1] - apos)/sa * run * alen;
			vb = (DB[bIdx+1] - bpos)/sb * run * blen;
			mnDist = min(mnDist, distToSeg(bpos, bpos+vb-va, apos));
			mxDist = max(mxDist, dist(apos, bpos));
			mxDist = max(mxDist, dist(apos, bpos+vb-va));
			apos = apos + va;
			bpos = bpos + vb;
			if(apos == DA[aIdx+1])
				aIdx++;
			if(bpos == DB[bIdx+1])
				bIdx++;
		}
		printf("Case %d: %.0lf\n", ++cases, mxDist - mnDist);
	} 
	return 0;
}
/*
2
2 2
0 0 10 0
0 1 10 1
3 2
635 187 241 269 308 254
117 663 760 413

5
10 10
30 66 38 52 5 84 32 1 32 52 42 31 7 42 46 76 18 80 29 89 
0 6 78 53 0 92 3 60 39 35 65 7 7 94 87 80 24 2 18 4 
10 10
62 0 47 7 90 45 69 59 68 86 13 35 0 14 20 86 15 64 88 84 
12 13 69 8 88 25 9 34 15 5 30 64 60 38 70 40 75 43 13 16 
10 10
37 84 79 52 60 5 0 43 31 85 4 0 55 13 22 43 63 24 88 29 
10 92 20 84 12 32 93 14 74 19 85 95 21 69 62 85 3 69 42 80 
10 10
48 39 95 35 56 23 19 33 66 89 9 35 56 10 84 40 64 19 23 66 
23 1 37 21 51 9 22 98 7 9 82 62 1 46 2 7 59 15 4 5 
10 10
59 54 11 12 27 89 31 50 73 36 33 60 6 69 70 26 93 32 20 46 
66 80 33 25 31 90 92 88 60 77 98 96 78 45 34 45 41 40 12 4 

*/
