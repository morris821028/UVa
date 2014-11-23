#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
using namespace std;
#define eps 1e-6
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
struct seg {
	Pt s, e;
	int label;
	seg(Pt a, Pt b):s(a), e(b) {}
};
struct CMP {
	static double y;
	
	double interpolate(const Pt& p1, const Pt& p2, double& y) {
        if (p1.y == p2.y) return p1.x;
        return p1.x + (double)(p2.x - p1.x) / (p2.y - p1.y) * (y - p1.y);
    }
    
	bool operator()(const seg &i, const seg &j) {
		double v1 = interpolate(i.s, i.e, y), v2 = interpolate(j.s, j.e, y);
		if (fabs(v1 - v2) > eps)
			return v1 < v2;
		return false;
	}
};
double CMP::y = 0;
int main() {	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	int n;
	double x, y, up, down;
	char cmd[10];
	while (scanf("%d", &n) == 1) {
		set<seg, CMP> S;
		for (int i = 0, k = 1; i < n; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'A') {
				scanf("%lf %lf", &up, &down);
				seg tmp = seg(Pt(up, 1), Pt(down, 0));
				tmp.label = k;
				S.insert(tmp), k++;
			} else {
				scanf("%lf %lf", &x, &y);
				CMP::y = y;
				set<seg>::iterator it = S.lower_bound(seg(Pt(x, 1), Pt(x, 1))), jt;
				if (it != S.end()) {
					if (onSeg(it->s, it->e, Pt(x, y))) {
						puts("[?, ?]");
						continue;
					}
				}
				int l = -1, r = -1;
				if (it != S.begin()) {
					jt = it, jt--;
					l = jt->label;
					if (onSeg(jt->s, jt->e, Pt(x, y))) {
						puts("[?, ?]");
						continue;
					}
				}
				if (it != S.end())
					r = it->label;
				if (l == -1)
					printf("[S, ");
				else
					printf("[%d, ", l);
				if (r == -1)
					printf("M]");
				else
					printf("%d]", r);
				puts("");
			}
		}
	}
	return 0;
}
/*
8
A 0 0
Q -1 0
Q 1 0
Q 0 0
A 1 2
Q 1 0.5
Q 3 0.5
Q 1.5 0.5
*/
