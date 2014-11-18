#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
// similar 11796 - Dog Distance
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
		scanf("%lf %lf", &DB[0].x, &DB[0].y);
		scanf("%lf %lf", &DA[0].x, &DA[0].y);
		scanf("%d", &A);
		for(int i = 1; i <= A; i++)
			scanf("%lf %lf", &DA[i].x, &DA[i].y);
		scanf("%d", &B);
		for(int i = 1; i <= B; i++)
			scanf("%lf %lf", &DB[i].x, &DB[i].y);
		A++, B++;
		double speed_a = 1, speed_b = 1;
		
		int aIdx, bIdx;
		double sa, sb, run;
		Vector va, vb;
		Pt apos = DA[0], bpos = DB[0];
		aIdx = bIdx = 0;
		
		double mxDist = 0, mnDist = 1e+30;
		while(aIdx < A - 1 && bIdx < B - 1) {
			sa = dist(DA[aIdx+1], apos);
			sb = dist(DB[bIdx+1], bpos);
			run = min(sa/speed_a, sb/speed_b); // run time
			va = (DA[aIdx+1] - apos)/sa * run * speed_a;
			vb = (DB[bIdx+1] - bpos)/sb * run * speed_b;
			if (bpos + vb == DB[B - 1] && apos + va == DA[A - 1]) { // a route is safe even if the villagers meet Leporello at the destination.
				mnDist = min(mnDist, dist(bpos, apos));
				if (!(bpos == bpos+vb-va) && between(bpos, bpos+vb-va, apos) && !(apos == bpos+vb-va))
					mnDist = min(mnDist, distProjection(bpos, bpos+vb-va, apos));
			} else
				mnDist = min(mnDist, distToSeg(bpos, bpos+vb-va, apos));
//			mxDist = max(mxDist, dist(apos, bpos));
//			mxDist = max(mxDist, dist(apos, bpos+vb-va));
			apos = apos + va;
			bpos = bpos + vb;
			if(apos == DA[aIdx+1])
				aIdx++;
			if(bpos == DB[bIdx+1])
				bIdx++;
		}
		if (cases++)	puts("");
		if (fabs(mnDist) < eps)
			puts("No");
		else
			puts("Yes");
	} 
	return 0;
}
/*

*/
