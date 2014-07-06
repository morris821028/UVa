#include <stdio.h>
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
double distProjection(Pt as, Pt at, Pt s) {
	double a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
struct Seg {
    Pt s, e;
};
int calcIntersection(Seg a, Seg b, Pt &p) {
    double a1, b1, c1, a2, b2, c2;
    double d, dx, dy;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x;
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    d = a1*b2 - a2*b1;
    dx = c1*b2 - c2*b1;
    dy = a1*c2 - a2*c1;
    if(fabs(d) < eps) // NONE or LINE
        return 0;
    p.x = dx / d, p.y = dy / d;
    /*printf("%lf %lf - %lf %lf\n", a.s.x, a.s.y, a.e.x, a.e.y);
    printf("%lf %lf - %lf %lf\n", b.s.x, b.s.y, b.e.x, b.e.y);
    printf("%lf %lf\n", p.x, p.y);*/
    return onSeg(a.s, a.e, p) && onSeg(b.s, b.e, p);
}
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
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

#define INF 1e+30 
double smallRect(int n, Pt ch[]) {
	double lx, ly, rx, ry;
	int up, down, left, right;
	double ret = INF;
	lx = ly = INF;
	rx = ry = -INF;
	
	up = down = left = right = 0;
	for(int i = 0; i < n; i++) {
		if(ch[i].x > rx)	rx = ch[i].x, right = i;
		if(ch[i].y > ry)	ry = ch[i].y, up = i;
		if(ch[i].x < lx)	lx = ch[i].x, left = i;
		if(ch[i].y < ly)	ly = ch[i].y, down = i;
	}
	
	int corner[] = {up, down, left, right};
	Pt vec[] = {Pt(-1, 0), Pt(1, 0), Pt(0, -1), Pt(0, 1)};
	
	ret = (rx - lx) * (ry - ly);
	for(int j = 0; j < 4; j++) {
		while(true) {
			Pt a = ch[corner[j]], b = ch[(corner[j]+1)%n], c = vec[j];
			if(fabs(cross2(b - a, c)) < eps)
				corner[j] = (corner[j] + 1)%n;
			else
				break;
		}
	}
//	for(int j = 0; j < 4; j++) {
//		Pt a = ch[corner[j]], b = vec[j];
//		printf("Pt[%lf %lf], Vector[%lf %lf]\n", a.x, a.y, b.x, b.y);
//	}	
	for(int i = 0; i < n; i++) {
		double mxVal = -INF, cos, sin;
		int mxIdx = 0;
		for(int j = 0; j < 4; j++) {
			Pt a = ch[corner[j]], b = ch[(corner[j]+1)%n], c = vec[j];
			double cosA = dot(b - a, c) / dist(b, a) / dist(c, Pt(0, 0));
			if(mxVal < cosA)
				mxVal = cosA, mxIdx = j;
//			printf("cos %lf\n", cosA);
		}
		cos = mxVal, sin = sqrt(1 - cos * cos);
//		printf("sin %lf cos %lf\n", sin, cos);
		for(int j = 0; j < 4; j++) {
			double tx, ty;
			tx = vec[j].x * cos - vec[j].y * sin;
			ty = vec[j].x * sin + vec[j].y * cos;
			vec[j] = Pt(tx, ty);
//			printf("%lf %lf\n", tx, ty);
		}
//		for(int j = 0; j < 4; j++) {
//			Pt a = ch[corner[j]], b = vec[j];
//			printf("Pt[%lf %lf], Vector[%lf %lf]\n", a.x, a.y, b.x, b.y);
//		}		
		for(int j = 0; j < 4; j++) {
			while(true) {
				Pt a = ch[corner[j]], b = ch[(corner[j]+1)%n], c = vec[j];
				if(fabs(cross2(b - a, c)) < eps)
					corner[j] = (corner[j] + 1)%n;
				else
					break;
			}
		}
		double w = distProjection(ch[corner[0]], ch[corner[0]]+vec[0], ch[corner[1]]);
		double h = distProjection(ch[corner[2]], ch[corner[2]]+vec[2], ch[corner[3]]);
//		printf("w %lf h %lf area %lf\n\n", w, h, w * h);
		ret = min(ret, w * h);
	}
	return ret;
}
int main() {
    Pt p[2048], ch[2048];
    int n, m;
    int testcase, cases = 0;
    while(scanf("%d", &n) == 1 && n) {
    	for(int i = 0; i < n; i++)
    		scanf("%lf %lf", &p[i].x, &p[i].y);
        m = monotone(n, p, ch);
//        for(int i = 0; i < m; i++)
//        	printf("%lf %lf\n", ch[i].x, ch[i].y);
    	
    	if(m < 3) {
    		printf("%.4lf\n", 0);
    		continue;
    	}
		double ret = smallRect(m, ch);
		printf("%.4lf\n", ret);
    }
    return 0;
}
/*
4
0 5
-5 0
5 0
0 -5
0 
*/
