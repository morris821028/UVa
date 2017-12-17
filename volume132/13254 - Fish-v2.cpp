#include <stdio.h>
#include <math.h>
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
int cmpZero(double x) {  
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1: -1;
}  
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if (as == at && bs == bt)
        return as == bs;
    if (as == at)
        return onSeg(bs, bt, as);
    if (bs == bt)
        return onSeg(as, at, bs);
    if (onSeg(as, at, bs) || onSeg(as, at, bt) || onSeg(bs, bt, as) || onSeg(bs, bt, at))
    	return 1;
	double c1 = cross(as, at, bs), c2 = cross(as, at, bt);
    double c3 = cross(bs, bt, as), c4 = cross(bs, bt, at);
    return cmpZero(c1)*cmpZero(c2) < 0 && cmpZero(c3)*cmpZero(c4) < 0;
}
int convexContain(int n, Pt p[], Pt q) {
    if (n < 3)	return false;
    if (cross(p[0], q, p[1]) > eps)		return 0;
    if (cross(p[0], q, p[n-1]) < -eps)	return 0;
    int l = 2, r = n - 1;
    int line = -1;
    while (l <= r) {
        int mid = (l + r)>>1;
        if (cross(p[0], q, p[mid]) > -eps) {
            line = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }
    return cross(p[line-1], q, p[line]) < eps;
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for (int i = n-1, t = m+1; i >= 0; i--) {
        while (m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
const int MAXN = 512;
int main() {
    int n, r;
    int x, y;
    char cmd[8];
    Pt A[MAXN], B[MAXN], chA[MAXN], chB[MAXN];
    while (scanf("%d %d", &n, &r) == 2 && n) {
        int aN = 0, bN = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %s", &x, &y, cmd);
            if (cmd[0] == 'A')
                A[aN++] = Pt(x, y);
            else
                B[bN++] = Pt(x, y);
        }
        aN = monotone(aN, A, chA);
        bN = monotone(bN, B, chB);
        int hasIntersect = 0;
        for (int i = 0; i < aN && !hasIntersect; i++) {
            if (convexContain(bN, chB, chA[i]))
                hasIntersect = 1;
        }
        for (int i = 0; i < bN && !hasIntersect; i++) {
            if (convexContain(aN, chA, chB[i]))
                hasIntersect = 1;
        }
        for (int i = 0, j = aN-1; i < aN && !hasIntersect; j = i++) {
            for (int p = 0, q = bN-1; p < bN; q = p++) {
                if (intersection(chA[i], chA[j], chB[p], chB[q])) {
                    hasIntersect = 1;
                    break;
                }
            }
        }
        puts(!hasIntersect ? "FEED" : "NOT YET");
    }
    return 0;
}
/*
 8 100
 0 0 A
 1 0 A
 1 1 A
 0 1 A
 -2 -2 B
 -2 2 B
 2 2 B
 2 -2 B
 
 8 100
 0 0 A
 2 0 A
 2 1 A
 0 1 A
 1 0 B
 5 0 B
 5 1 B
 1 1 B
 
 5 100
 0 0 A
 2 0 A
 2 1 A
 0 1 A
 1 0 B
 
 10 3
 0 0 A
 -2 0 A
 -1 -1 A
 -1 -2 A
 1 -2 A
 1 1 B
 0 1 B
 1 0 B
 2 0 B
 2 -1 B
 9 3
 0 0 A
 -1 -1 A
 -2 -1 A
 2 -1 A
 1 1 A
 -1 1 B
 1 -1 B
 0 2 B
 0 -2 B
 */
