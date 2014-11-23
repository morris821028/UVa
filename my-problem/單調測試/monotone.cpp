#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

#define eps 1e-10
#define MAXN 32767
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator*(const double &a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
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
Pt getIntersect(Pt l1, Pt p1, Pt l2, Pt p2) {
	double a1, b1, c1, a2, b2, c2;
	double dx, dy, d;
	a1 = l1.y, b1 = -l1.x;
	c1 = a1 * p1.x + b1 * p1.y;
	a2 = l2.y, b2 = -l2.x;
	c2 = a2 * p2.x + b2 * p2.y;
	dx = c1 * b2 - c2 * b1, dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
	return Pt(dx/d, dy/d);
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
struct CMP2 {
    bool operator()(const double &i, const double &j) const {
        if (fabs(i-j) > eps)
            return i < j;
        return false;
    }
};
Seg segs[MAXN];
Pt D[MAXN];
int testMonotone(int n, Pt D[]) {
    int m = 0, origin_n = n;
    D[n] = D[0], D[n+1] = D[1];
    for (int i = 1; i <= n; i++) {
        Pt v1 = D[i + 1] - D[i];
        Pt v2 = D[i - 1] - D[i];
        segs[m++] = Seg(v1, v2, i);
        segs[m++] = Seg(v1 * -1, v2 * -1, i);
    }
    n = m;
    Pt pos = Pt(0, 0);
    set<int> S;
    map<double, vector< pair<int, int> >, CMP2> angle;
    for (int i = 0; i < n; i++) {
        double v1 = atan2(segs[i].s.y - pos.y, segs[i].s.x - pos.x);
        double v2 = atan2(segs[i].e.y - pos.y, segs[i].e.x - pos.x);
        angle[v1].push_back(make_pair(i, 0));
        angle[v2].push_back(make_pair(i, 1));
    }
    double c;
    pair<int, int> u = angle.begin()->second[0];
    Pt fpt;
    if (u.second == 0)  fpt = segs[u.first].s;
    else                fpt = segs[u.first].e;
    for (int i = 0; i < n; i++) {
		if (cross(pos, fpt, segs[i].s) * cross(pos, fpt, segs[i].e) < 0) {
			Pt q = getIntersect(segs[i].s - segs[i].e, segs[i].s, fpt - pos, pos);
			if (dot(q - pos, fpt - pos) > 0)
				S.insert(segs[i].label);
		} 
    }
    for (map<double, vector< pair<int, int> >, CMP2>::iterator it = angle.begin();
         it != angle.end(); it++) {
        for (int i = 0; i < it->second.size(); i++) {
            pair<int, int> u = it->second[i];
            if (u.second == 0)
                c = cross(pos, segs[u.first].s, segs[u.first].e);
            else
                c = cross(pos, segs[u.first].e, segs[u.first].s);
            if (fabs(c) > eps) {
                if (c > 0)
                    S.insert(segs[u.first].label);
                else
                    S.erase(segs[u.first].label);
            }
        }
        if (S.size() >= origin_n - 2)
            return 1;
    }
    return 0;
}
int main() {
    int n;
    double x, y;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &y);
            D[i] = Pt(x, y);
        }
        int flag = testMonotone(n, D);
        puts(flag ? "yes" : "no");
    }
    return 0;
}
/*
 8
 -2 0
 1 -1
 4 0
 3 2
 2 0
 1 3
 0 0
 -1 2
 
 8
 1 2
 2 2
 2 3
 -1 3
 -1 -2
 2 -2
 2 -1
 1 -1 
 
 48 
 -2.46 7.26
 -1.3 7.86
 0 8
 1.22 7.74
 1.4 8.38
 2.42 7.36 3.2 7.4
 2.9 6.58
 3.72 5.12
 3.78 4.1
 4.26 3.42
 4.86 2.36
 4.74 1.92
 4 1
 4 1.48
 3.66 1.26
 3.36 1.84
 3.18 1.28
 2.94 1.66
 2 1
 2.04 1.44
 1.14 1.02
 1.76 -0.16
 1.68 -1.12
 1.4 -1.42
 2.06 -4.68
 1.72 -5.68
 1.4 -6
 1 -6
 0.26 -5.52
 -0.54 -5.66
 -1 -6
 -2 -4 
 -1.78 -1.4
 -2.14 -0.8
 -1.4 0.68
 -1.6 0.98
 -2.62 1.58
 -2.66 1.04
 -3.36 1.74
 -3.74 1.12
 -4.28 1.36
 -4.18 2.14 
 -3.54 3.62
 -3 6
 -3.7 4.9
 -3.88 3.66
 -3.98 5.14 
 */
