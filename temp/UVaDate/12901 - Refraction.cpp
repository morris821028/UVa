#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <algorithm>
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

double W, H, pos_x, eye_x, eye_y, mu;
Pt eye, A, B, C, D;
double getViewX(double h) {
	Pt p(0, h), q(W, h);
	Pt r = getIntersect(Seg(eye, A), Seg(p, q));
	Pt ab = eye - A, bc;
	double sin_alpha = (ab.x) / ab.length();
	double cos_alpha = (ab.y) / ab.length();
	double sin_beta = sin_alpha / mu;
	double cos_beta = cos(asin(sin_beta));
	double sin = sin_alpha * cos_beta - cos_alpha * sin_beta;
	double cos = cos_alpha * cos_beta + sin_alpha * sin_beta;
	bc.x = ab.x * cos - ab.y * sin;
	bc.y = ab.x * sin + ab.y * cos;
	Pt u = getIntersect(Seg(r, r + bc), Seg(B, C));
	return min(max(-1.0, u.x), W + 1);
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf %lf %lf %lf %lf", &W, &H, &pos_x, &eye_x, &eye_y, &mu);
		eye = Pt(eye_x, eye_y);
		A = Pt(W, H), B = Pt(W, 0), C = Pt(0, 0), D = Pt(0, H);
		
		double l = 0, r = H, mid;
		double mn_h = -1;
		for (int i = 0; i < 50; i++) {
			mid = (l + r)/2;
			if (getViewX(mid) >= pos_x - 1e-9)
				r = mid, mn_h = mid;
			else
				l = mid;
		}
		if (mn_h >= 0)
			printf("%.4lf\n", mn_h);
		else
			printf("Impossible\n");
	}
	return 0;
}
/*
8
100 150 30 200 200 3.0000
100 150 0 200 200 3.0000
150 150 0 200 200 3.0000
100 150 30 200 200 2.0000
100 150 100 200 200 2.0000
533 543 354 792 933 2.007965
510 504 131 528 519 2.161657
555 563 460 582 637 4.656606
*/
