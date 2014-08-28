#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;
#define eps 1e-10
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
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}

double g(Pt a, Pt b, double x) {
    Pt vab = b - a;
    return a.y + vab.y * (x - a.x) / vab.x;
}
int inside_convex(const Pt &p, Pt ch[], int n) {
	if(n < 3)
        return false;
	if(cross(ch[0], p, ch[1]) > eps)
        return false;
	if(cross(ch[0], p, ch[n-1]) < -eps)
        return false;
    
	int l = 2, r = n-1;
	int line = -1;
	while(l <= r) {
		int mid = (l + r)>>1;
		if(cross(ch[0],p, ch[mid]) > -eps) {
			line = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return cross(ch[line-1], p, ch[line]) < eps;
}
Pt D[131072], ch[262144];
int main() {
    int testcase, n, m;
    double x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &y);
            ch[i] = Pt(x, y);
        }
//        n = monotone(n, D, ch);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%lf %lf", &x, &y);
            int f = inside_convex(Pt(x, y), ch, n);
            puts(f ? "y" : "n");
        }
        
    }
    return 0;
}
/*
 1
 3
 0 0
 10 0
 5 5
 4
 0 0
 1 2
 5 6
 4 3
 */