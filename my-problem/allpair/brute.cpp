#include <stdio.h>
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map> 
#include <functional>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x < a.x;
        if(fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator>(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x > a.x;
        if(fabs(y - a.y) > eps)	return y > a.y;
        return false;
    }
    bool operator!=(const Pt &a) const {
        return fabs(x - a.x) > eps || fabs(y - a.y) > eps;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    void print() const {
    	double px = x, py = y;
    	if (fabs(x) < eps)	px = 0;
    	if (fabs(y) < eps)	py = 0;
    	printf("%.6lf %.6lf\n", px, py);
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
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) <= 0 &&
       cross(at, as, bs) * cross(at, as, bt) <= 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}
Pt intersectionPt(Pt as, Pt at, Pt bs, Pt bt) {
	double a1, a2, b1, b2, c1, c2, dx, dy, d;
	a1 = as.y - at.y, b1 = -(as.x - at.x), c1 = as.x * a1 + as.y * b1;
	a2 = bs.y - bt.y, b2 = -(bs.x - bt.x), c2 = bs.x * a2 + bs.y * b2;
	dx = c1 * b2 - c2 * b1;
	dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
    return Pt(dx/d, dy/d);
}
struct seg {
	Pt s, e;
	seg(Pt a, Pt b):s(a), e(b) {}
	bool operator<(const seg &a) const {
        if (s != a.s)	return s < a.s;
        return e < a.e;
    }
};
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 

	int testcase, n;
	double sx, sy, ex, ey;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		vector<seg> segs;
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
			segs.push_back(seg(Pt(sx, sy), Pt(ex, ey)));
		}
		set<Pt> S;
		for (int i = 0; i < segs.size(); i++) {
			for (int j = i + 1; j < segs.size(); j++) {
				if (intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e)) {
					S.insert(intersectionPt(segs[i].s, segs[i].e, segs[j].s, segs[j].e));
				}
			}
		}
		printf("%d\n", S.size());
		for (set<Pt>::iterator it = S.begin(); it != S.end(); it++) {
			it->print();
		}
		puts("");
	}
	return 0;
}
/*
50
10
43 60 91 39
34 96 6 94
29 39 74 49
81 15 80 5
29 76 52 34
41 40 37 5
51 82 38 89
54 27 81 50
44 81 90 23
4 31 54 50

10
32 34 57 24
4 16 20 19
20 7 48 88
17 62 80 21
57 19 56 21
95 9 99 45
64 85 50 64
26 81 30 2
20 73 92 87
34 47 22 91

4
0 4 6 0
0 0 6 4
2 6 8 0
2 -2 4 2

2
0 0 0 1
0 1 2 3

6
1 4 2 -2
5 4 7 -4
5.5 -4 6 0
4 -2 9 3
3 4 6 0
2 1 6 0


Output
3 2
3.75 1.5
4.8 3.2
*/
