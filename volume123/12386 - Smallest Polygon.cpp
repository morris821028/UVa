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
using namespace std;
#define eps 1e-9
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
	return dot(c - a, b - a) > 0 && dot(c - b, a - b) > 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
struct Seg {
    Pt s, e;
};
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < -eps &&
       cross(at, as, bs) * cross(at, as, bt) < -eps &&
       cross(bs, bt, as) * cross(bs, bt, at) < -eps &&
       cross(bt, bs, as) * cross(bt, bs, at) < -eps)
        return 1;
    return 0;
}
double calcArea(Pt p[], int n) {
    if(n < 3)   return 0.0;
    double ret = 0;
    int i;
    p[n] = p[0];
    for(i = 0; i < n; i++)
        ret += p[i].x * p[i+1].y - p[i].y * p[i+1].x;
    return fabs(ret)/2;
}
double calcPer(Pt p[], int n) {
    double ret = 0;
    int i;
    p[n] = p[0];
    for(i = 0; i < n; i++)
        ret += dist(p[i], p[i+1]);
    return ret;
}
#define INF 1e+8
Pt p[16], path[16];
double mn_area, mn_area_per, mn_per;
int used[16], n;
int check(Pt a, Pt b, int l, int r) {
    for (int i = l; i < r; i++) {
        if (intersection(a, b, path[i], path[i+1]))
            return 0;
        if (onSeg(path[i], path[i+1], a))
            return 0;
        if (onSeg(path[i], path[i+1], b))
            return 0;
        if (onSeg(a, b, path[i]) || onSeg(a, b, path[i+1]))
            return 0;
    }
    return 1;
}
void dfs(int idx) {
    if (idx == n) {
        if (check(path[n-1], path[0], 0, n-1)) {
            double t = calcArea(path, n), c = calcPer(path, n);
            if (mn_area > t || (fabs(mn_area - t) < eps && mn_area_per > c)) {
                mn_area = t;
                mn_area_per = c;
            }
            mn_per = min(mn_per, calcPer(path, n));
        }
        return ;
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            path[idx] = p[i];
            if (check(path[idx], path[idx-1], 0, idx-1))
                dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
    	for(int i = 0; i < n; i++)
    		scanf("%lf %lf", &p[i].x, &p[i].y);
        mn_area = mn_per = INF;
        memset(used, 0, sizeof(used));
        path[0] = p[0], used[0] = 1;
        dfs(1);
        printf("%.4lf\n", fabs(mn_area_per - mn_per));
    }
    return 0;
}

/*
 20
 7
 84 43
 43 64
 40 69
 22 75
 27 94
 68 71
 64 4
 
> 65.6943
 
 2
 3
 1 1
 1 2
 2 1
 4
 0 0
 1 1
 0 2
 2 1
 */
