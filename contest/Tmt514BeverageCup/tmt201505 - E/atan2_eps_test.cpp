#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <time.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
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
struct Seg {
	Pt s, e;
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
//		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
	bool operator!=(const Seg &other) const {
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
	return acos(dot(va, vb) / va.length() / vb.length());
}	
double distSeg2Point(Pt a, Pt b, Pt p) {
	Pt c, vab;
	vab = a - b;
	if (between(a, b, p)) {
		c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
		return (p - c).length();
	}
	return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
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
const double pi = acos(-1);

int main() {
	srand ( time(NULL));
	
	vector< pair<double, Pt> > V;
	for (int i = 0; i < 10000000; i++) {
		int X, Y;
		X = (rand()*rand())%2000000 - 1000000;
		Y = (rand()*rand())%2000000 - 1000000;
		V.push_back(make_pair(atan2(Y, X), Pt(X, Y)));
	}
	sort(V.begin(), V.end());
	for (int i = 0; i+1 < V.size(); i++) {
		if (cross2(V[i].second, V[i+1].second) != 0 && fabs(V[i].first - V[i+1].first) < 1e-12)
			printf("%.0lf %.0lf %.0lf %.0lf\n", V[i].second.x, V[i].second.y, V[i+1].second.x, V[i+1].second.y);
	}

//	long long a = 599430;
//	long long b = 1428722;
//	long long c = 648824;
//	long long d = 1546451;

//	long long a = 885828;
//	long long b = 737167;
//	long long c = 898961;
//	long long d = 748096;
//
//	printf("%lld\n", a * d - b * c);
//	printf("%lf %lf, %d\n", atan2(b, a), atan2(d, c), fabs(atan2(b, a) - atan2(d, c)) < 1e-12);
	return 0;
}
/*
885828 737167 898961 748096
854425 732894 706721 606199
-971645 988877 -838743 853618
993753 -652232 991850 -650983
620105 659001 916399 973880
*/
