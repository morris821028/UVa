#include <bits/stdc++.h>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if (fabs(x-a.x) > eps)	return x < a.x;
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
int cmpZero(double x) {  
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1: -1;
}  
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
int intersection(Pt as, Pt at, Pt bs, Pt bt) {	// not include end point
    double c1 = cross(as, at, bs), c2 = cross(as, at, bt);
    double c3 = cross(bs, bt, as), c4 = cross(bs, bt, at);
    return cmpZero(c1)*cmpZero(c2) < 0 && cmpZero(c3)*cmpZero(c4) < 0;
}
int convexContain(int n, Pt p[], Pt q) {	// include point on edge
	if (n == 2) {
		if (q.x < min(p[0].x, p[1].x) || q.x > max(p[0].x, p[1].x))
			return 0;  
        if (q.y < min(p[0].y, p[1].y) || q.y > max(p[0].y, p[1].y))
			return 0;
	}
    for (int i = 0, j = n-1; i < n; j = i++) {
    	if (cross(p[j], p[i], q) < 0)
    		return 0;
	}
	return 1;
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
int hasLinearClassifier(Pt A[], int aN, Pt B[], int bN) {
	static Pt chA[MAXN*2], chB[MAXN*2];
	int aM, bM;
	if (aN == 1 && bN == 1)
		return 1;
	if (aN == 1) {
		bM = monotone(bN, B, chB);
		if (convexContain(bM, chB, A[0]))
			return 0;
	} else if (bN == 1) {
		aM = monotone(aN, A, chA);
		if (convexContain(aM, chA, B[0]))
			return 0;
	} else {
		aM = monotone(aN, A, chA);
	    bM = monotone(bN, B, chB);
	    for (int i = 0, j = aM-1; i < aM; j = i++) {
	        for (int p = 0, q = bM-1; p < bM; q = p++) {
	            if (intersection(chA[i], chA[j], chB[p], chB[q]))
	            	return 0;
	        }
	    }
	    for (int i = 0; i < aM; i++) {
	        if (convexContain(bM, chB, chA[i]))
	            return 0;
	    }
	    for (int i = 0; i < bM; i++) {
	        if (convexContain(aM, chA, chB[i]))
	            return 0;
	    }
	}
    return 1;
}
int main() {
    int n, r;
    int x, y;
    char cmd[8];
    Pt A[MAXN], B[MAXN];
    while (scanf("%d %d", &n, &r) == 2 && n) {
    	assert(n < MAXN);
        int aN = 0, bN = 0;
        for (int i = 0; i < n; i++) {
            assert(scanf("%d %d %s", &x, &y, cmd) == 3);
            if (cmd[0] == 'A')
                A[aN++] = Pt(x, y);
            else if (cmd[0] == 'B')
                B[bN++] = Pt(x, y);
        }
        assert(aN && bN);
        int ret = hasLinearClassifier(A, aN, B, bN);
        puts(ret ? "FEED" : "NOT YET");
    }
    return 0;
}
/*

10 1000
1 4 A
1 9 B
6 5 A
8 2 A
2 9 B
8 9 A
10 4 A
1 6 B
6 7 A
5 9 A

10 1000
9 6 A
3 1 B
3 9 B
3 7 A
8 9 A
5 7 A
6 1 A
4 8 A
8 1 A
7 4 A

5 100
-1 1 B
1 1 B
1 -1 B
-1 -1 B
0 0 A

6 100
-1 1 B
1 1 B
1 -1 B
-1 -1 B
-2 -2 A
2 2 A

4 100
-1 0 A
1 0 A
0 1 B
0 -1 B

4 100
-1 1 A
-1 -1 A
1 0 B
2 0 B 
6 100
0 2 A 
0 -2 A 
-1 0 A
0 1 B
0 -1 B
1 0  B
 
3 100
-1 0 A 
1 0 A 
0 0 B 

3 100
-1 0 A 
1 0 B 
0 0 A 

2 100
0 1 B 
1 0 A 
5 100
-1 1 A 
-1 -1 A
1 -1 A
1 1 A
0 0 B

7 100
-1 1 A
-1 -1 A
1 -1 A
1 1 A
0 2 B
-1 -2 B
1 -2 B

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
 
