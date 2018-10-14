#include <bits/stdc++.h> 
using namespace std;

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int ReadFloat(double *x) {
	static char c, neg, buf[32];
	char *ptr = buf;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    *ptr = c, ptr++;
    while((c = readchar()) >= '-')
        *ptr = c, ptr++;
    *ptr = '\0';
    *x = atof(buf);
    return 1;
}
const double eps = 1e-6;
struct Pt {
    double x, y;
    Pt() {}
    Pt(double a, double b): x(a), y(b) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y); }
    Pt operator*(const double a) const { return Pt(x * a, y * a);  }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    int read() {
    	return ReadFloat(&x) && ReadFloat(&y);
//    	return scanf("%lf %lf", &x, &y) == 2;
	}
    void println() const {
    	printf("(%lf, %lf)\n", x, y);
    }
    double length() const {
    	return hypot(x, y);
	}
};
struct Seg {
    Pt s, e;
    Seg() {}
    Seg(Pt a, Pt b):s(a), e(b) {}
    void println() {
    	printf("Segment((%lf, %lf), (%lf, %lf))\n", s.x, s.y, e.x, e.y);
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
int cmpZero(float v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}

static inline int fastIntersection(const Seg &sa, const Seg &sb) {
    double ax = sa.e.x-sa.s.x, ay = sa.e.y-sa.s.y;
    double bx = sb.s.x-sb.e.x, by = sb.s.y-sb.e.y;
    double cx = sa.s.x-sb.s.x, cy = sa.s.y-sb.s.y;
    double alphaX = by*cx - bx*cy;
    double Y = ay*bx - ax*by;
    if (Y == 0) {                        // parallel
        double betaX = ax*cy - ay*cx;
        if (alphaX != 0 || betaX != 0)    // no-colinear
            return 0;
        if (ax == 0)
            return max(min(sa.s.y, sa.e.y), min(sb.s.y, sb.e.y)) <=
                min(max(sa.s.y, sa.e.y), max(sb.s.y, sb.e.y));
        else
            return max(min(sa.s.x, sa.e.x), min(sb.s.x, sb.e.x)) <=
                min(max(sa.s.x, sa.e.x), max(sb.s.x, sb.e.x));
        return 0;
    }
    if (Y > 0) {
        if (alphaX < 0 || alphaX > Y)
            return 0;
    } else {
        if (alphaX > 0 || alphaX < Y)
            return 0;
    }
    double betaX = ax*cy - ay*cx;
    if (Y > 0) {
        if (betaX < 0 || betaX > Y)
            return 0;
    } else {
        if (betaX > 0 || betaX < Y)
            return 0;
    }
    return 1;
}

int read(Pt A[], Pt B[]) {
	for (int i = 0; i < 4; i++)	
		A[i].read();
	for (int i = 0; i < 4; i++)	
		B[i].read();
	int zero = 1;
	for (int i = 0; i < 4; i++) {
		zero &= cmpZero(A[i].x) == 0 && cmpZero(A[i].y) == 0;
		zero &= cmpZero(B[i].x) == 0 && cmpZero(B[i].y) == 0;
	}
	return !zero;
}
int main() {
	Pt A[8], B[8];
	while (read(A, B)) {
		Pt cA(0, 0), cB(0, 0);
		for (int i = 0; i < 4; i++)
			cA = cA + A[i];
		for (int i = 0; i < 4; i++)
			cB = cB + B[i];
		cA = cA * (1.0/4);
		cB = cB * (1.0/4);
		
		Pt mv = (cB - cA)*4;

		for (int i = 0; i < 4; i++) {
			Pt ai = A[i];
			Pt mv_a = A[i] + mv;
			for (int p = 3, q = 0; q < 4; p = q++) {
				if (fastIntersection(Seg(B[p], B[q]), Seg(ai, mv_a)))
					mv_a = getIntersect(Seg(B[p], B[q]), Seg(ai, mv_a));
			}
			mv = mv - (mv_a - ai);
			A[i] = mv_a;
			if (cmpZero(mv.x) == 0 && cmpZero(mv.y) == 0)
				break;
		}
		for (int i = 0; i < 4; i++)
			printf("%.12lf %.12lf\n", A[i].x, A[i].y);
	}
	return 0;
}
/*
731.637000000000 437.595000000000 296.162000000000 402.836000000000
493.625000000000 260.917000000000 526.376000000000 237.611000000000
631.933553096878 841.348627667446 158.076619219714 651.913864882162
360.066446903122 146.651372332554 833.923380780286 336.086135117837
0.000000000000 0.000000000000 0.000000000000 0.000000000000
0.000000000000 0.000000000000 0.000000000000 0.000000000000
0.000000000000 0.000000000000 0.000000000000 0.000000000000
0.000000000000 0.000000000000 0.000000000000 0.000000000000
*/
