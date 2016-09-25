#include <bits/stdc++.h>
using namespace std;

#define eps 1e-6
#define MAXN 131072
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
double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
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
double dist2Seg(Pt a, Pt b, Pt o) {
	return fabs(cross(a, b, o)) / dist(a, b);
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		Pt o, A[32];
		int x, y;
		scanf("%d %d", &x, &y);
		o = Pt(x, y);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			A[i] = Pt(x, y);
		}
		double ret = dist(o, A[0]);
		for (int i = 1; i < n; i++)
			ret = min(ret, dist(o, A[i]));
		for (int i = 0, j = n-1; i < n; j = i++) {
			if (!between(A[i], A[j], o))
				continue;
			double t = dist2Seg(A[i], A[j], o);
			ret = min(ret, t);
		}
		printf("%.3lf\n", ret);
	}
	return 0;
}

