#include <bits/stdc++.h> 
using namespace std;

const double eps = 1e-10;
const int MAXN = 131072;
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
    Seg(Pt a = Pt(), Pt b = Pt(), int l=0): s(a), e(b), label(l) {
        angle = atan2(e.y - s.y, e.x - s.x);
    }
    bool operator<(const Seg &other) const {
        if (fabs(angle - other.angle) > eps)
            return angle > other.angle;
        if (cross(other.s, other.e, s) > -eps)
            return true;
        return false;
    }
};
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
int cmpZero(double x) {
	if (fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}
int halfPlaneIntersect(vector<Seg> segs, double &ret_yval) {
	static Seg deq[MAXN];
    sort(segs.begin(), segs.end());
    int n = segs.size(), m = 1;
    int front = 0, rear = -1;
    for (int i = 1; i < n; i++) {
        if (fabs(segs[i].angle - segs[m-1].angle) > eps)
            segs[m++] = segs[i];
    }
    n = m;
    if (n == 1) {
    	ret_yval = segs[0].s.y;
    	return 1;
	}
    deq[++rear] = segs[0];
    deq[++rear] = segs[1];
    for (int i = 2; i < n; i++) {
        while (front < rear && cross(segs[i].s, segs[i].e, getIntersect(deq[rear], deq[rear-1])) < eps)
            rear--;
        while (front < rear && cross(segs[i].s, segs[i].e, getIntersect(deq[front], deq[front+1])) < eps)
            front++;
        deq[++rear] = segs[i];
    }
    while (front < rear && cross(deq[front].s, deq[front].e, getIntersect(deq[rear], deq[rear-1])) < eps)
        rear--;  
    while (front < rear && cross(deq[rear].s, deq[rear].e, getIntersect(deq[front], deq[front+1])) < eps)
    	front++;
    
    int mn_has = 0;
    double mn_yval = -1;
    for (int i = front; i < rear; i++) {
        Pt p = getIntersect(deq[i], deq[i+1]);
        if (mn_has == 0 || (cmpZero(p.y - mn_yval) == -1))
        	mn_has = 1, mn_yval = p.y;
//        printf("ii1 %lf %lf %d\n", p.x, p.y, mn_yval);
    }
    if (rear > front + 1) {
        Pt p = getIntersect(deq[front], deq[rear]);
        if (mn_has == 0 || (cmpZero(p.y - mn_yval) == -1))
        	mn_has = 1, mn_yval = p.y;
//        printf("ii2 %lf %lf %d\n", p.x, p.y, mn_yval);
    } 
    ret_yval = mn_yval;
    return mn_has;
}

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		vector<Seg> segs;
		for (int i = 0; i < n; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			assert(abs(a) <= 300);
			assert(abs(b) <= 300);
			assert(abs(c) <= 300);
			Pt s, e;
			if (a == 0) {
				s = Pt(0, 1.f * c/b), e = Pt(1, 1.f * c/b);
			} else if (b == 0) {
				s = Pt(1.f * c/a, 0), e = Pt(1.f * c/a, 1);
			} else {
				s = Pt(0, 1.f * c/b), e = Pt(1, 1.f * (c-a)/b);
			}
			if (a && b) {
				if ((a > 0 && b > 0) ||
					(a < 0 && b > 0))
					swap(s, e);
			} else if (a == 0 && b > 0) {
				swap(s, e);
			} else if (b == 0 && a < 0) {
				swap(s, e);
			} else {
//				assert(false);
			}
//			printf("%lf %lf -> %lf %lf\n", s.x, s.y, e.x, e.y);
			segs.push_back(Seg(s, e, i));
		}
		// add bounding box
		const int MAXV = 200000;
		segs.push_back(Seg(Pt(-MAXV, -MAXV), Pt(MAXV, -MAXV), n));
		segs.push_back(Seg(Pt(MAXV, -MAXV), Pt(MAXV, MAXV), n+1));
		segs.push_back(Seg(Pt(MAXV, MAXV), Pt(-MAXV, MAXV), n+2));
		segs.push_back(Seg(Pt(-MAXV, MAXV), Pt(-MAXV, -MAXV), n+3));
		double mn_yval;
		int status = halfPlaneIntersect(segs, mn_yval);
		if (status == 0) {
			puts("NA");
		} else {
			if (cmpZero(mn_yval - -MAXV) == 0)
				puts("-INF");
			else
				printf("%lf\n", mn_yval);
		}
	}
	return 0;
}
/*
ax+by <= c
2
1 0 5
1 1 0
2
1 0 5
-1 -1 0
2
1 0 5
-1 0 6
2
1 0 5
-1 0 -6
1
0 -2 5
1
0 2 5
1
0 2 5
1
2 3 0 
2
2 -7 36
-2 -7 36
2
6 -21 108
-4 -1 18
*/

