#include <bits/stdc++.h>
using namespace std;

#define eps 1e-6
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
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
    double length() {
        return hypot(x, y);
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
};
const double pi = acos(-1);
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
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
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
		if (p[i] == p[j])
        	continue;
        if (onSeg(p[i], p[j], q))
            return 0;        
        if (p[i].y > q.y != p[j].y > q.y &&
        q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
        cnt++;
    }
    return cnt&1;
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	const int MAXN = 1024;
	Pt A[MAXN];
	while (testcase--) {
		scanf("%d %d", &n, &m);
		set<Pt> S;
		for (int i = 0; i < n; i++)
			A[i].read();
		int ret = 0;
		for (int i = 0; i < m; i++) {
			Pt q;
			q.read();
			if (inPolygon(A, n, q))
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
