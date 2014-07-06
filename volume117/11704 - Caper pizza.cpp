#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    int label;
    Pt(double a = 0, double b = 0, int c = 0):
    	x(a), y(b), label(c) {}
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
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
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
Pt pt[32767];
int make(int n, int A, int B) {
	A /= 2, B /= 2;
	Pt o(0, 0);
	int cntA = 0, cntB = 0, cut = 0;
	if(!pt[0].label)	cntA++;
	else				cntB++;
	for(int i = 1; i < n; i++) {
		if(cross(o, pt[0], pt[i]) > 0) {
			if(!pt[i].label)
				cntA++;
			else
				cntB++;
		} else {
			cut = i;
			break;
		}
	}
	if(cntA == A && cntB == B)
		return 1;
	for(int i = 1; i < n; i++) {
		if(!pt[i-1].label)
			cntA--;
		else
			cntB--;
		while(cross(o, pt[i], pt[cut]) > 0) {
			if(!pt[cut].label)
				cntA++;
			else
				cntB++;
			cut = (cut+1)%n;
		}
		if(cntA == A && cntB == B)
			return 1;
	}
	return 0;
}
int main() {
	int A, B, n;
	while(scanf("%d %d", &A, &B) == 2) {
		if(A == -1 && B == -1)
			break;
		n = 0;
		for(int i = 0; i < A; i++) {
			scanf("%lf %lf", &pt[n].x, &pt[n].y);
			pt[n++].label = 0;
		}
		for(int i = 0; i < B; i++) {
			scanf("%lf %lf", &pt[n].x, &pt[n].y);
			pt[n++].label = 1;
		}
		
		vector< pair<double, Pt> > v;
		for(int i = 0; i < n; i++) {
			v.push_back(make_pair(atan2(pt[i].y, pt[i].x), pt[i]));
		}
		sort(v.begin(), v.end());
		for(int i = 0; i < n; i++)
			pt[i] = v[i].second;
		
		puts(make(n, A, B) ? "YES" : "NO");
	}
	return 0;
}
/*
0 2
1 0
-1 0

0 2
1 0
0 1

2 2
1 1
1 0
0 1
-1 1

2 2
1 1
-1 1
0 1
0.1 -1

-1 -1
*/
