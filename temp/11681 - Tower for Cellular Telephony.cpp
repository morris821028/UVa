#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include <assert.h>
using namespace std;

#define eps 1e-5
#define MAXN 64
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
    Pt operator/(const double a) const {
        return Pt(x / a, y / a);
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
struct Seg {
	Pt s, e;
	Seg(Pt a = Pt(), Pt b = Pt()): s(a), e(b) {
	}
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dist2(Pt a, Pt b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
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
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
	double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
	return a.s + (a.e - a.s) * t;
}
Pt circle(Pt &a, Pt &b, Pt &c) {
    Pt ab, ac, o, vab, vac;
    static double a1, b1, c1, a2, b2, c2, D, D1, D2;
    ab = (a + b) / 2.0;
    ac = (a + c) / 2.0;
    vab = a - b, vac = a - c;
    swap(vab.x, vab.y);
    swap(vac.x, vac.y);
    vab.x = - vab.x, vac.x = - vac.x;
    return getIntersect(Seg(ab, ab + vab), Seg(ac, ac + vac));
}
double minCoverCircle(Pt p[], int n) {
    Pt c;
    double cr = 0.0;
    c = p[0];
    for (int i = 1; i < n; i++) {
        if (dist2(p[i], c) > cr + eps) {
            c = p[i], cr = 0;
            for (int j = 0; j < i; j++) {
                if (dist2(p[j], c) > cr + eps) {
                    c = (p[i] + p[j]) / 2.0;
                    cr = dist2(p[i], c);
                    for (int k = 0; k < j; k++) {
                        if(dist2(p[k], c) > cr + eps) {
                            c = circle(p[i], p[j], p[k]);
                            cr = dist2(p[i], c);
                        }
                    }
                }
            }
        }
    }
    return sqrt(cr);
}
int main() {
	int n;
	Pt D[MAXN], A[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &D[i].x, &D[i].y);
		
		double ret = 1e+30;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				Pt o = (D[i] + D[j]) /2.0;
				double r1 = dist(o, D[i]), r2;
				if (r1 > ret)	continue;
				int m = 0;
				for (int k = 0; k < n; k++) {
					if (dist(o, D[k]) > r1) {
						A[m++] = D[k];
					}
				}
				r2 = minCoverCircle(A, m);
				ret = min(ret, max(r1, r2));
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				for (int k = j+1; k < n; k++) {
					Pt o = circle(D[i], D[j], D[k]);
					double r1 = dist(o, D[i]), r2;
					if (r1 > ret)	continue;
					int m = 0;
					for (int k = 0; k < n; k++) {
						if (dist(o, D[k]) > r1 + eps) {
							A[m++] = D[k];
						}
					}
					r2 = minCoverCircle(A, m);
					ret = min(ret, max(r1, r2));
				}				
			}
		}
		printf("%.2lf\n", ret);
	}
	return 0;
}
/*
3
0 0
1 0
0 4
10
0 0
0 3
1 6
2 2
3 5
5 3
6 3
9 5
10 5
11 3
0
*/
