#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-6 
#define MAXN 32767
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
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
	double a1, b1, c1, a2, b2, c2;
	double dx, dy, d;
	a1 = a.s.y - a.e.y, b1 = a.e.x - a.s.x;
	c1 = a1 * a.s.x + b1 * a.s.y;
	a2 = b.s.y - b.e.y, b2 = b.e.x - b.s.x;
	c2 = a2 * b.s.x + b2 * b.s.y;
	dx = c1 * b2 - c2 * b1, dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
	return Pt(dx/d, dy/d);
}
Seg deq[MAXN];
int onIntersect[MAXN];
set<Pt> times[MAXN];
void halfPlaneIntersect(Seg segs[], int n) {
	sort(segs, segs + n);
	int m = 1;
	int front = 0, rear = -1;
	for (int i = 1; i < n; i++) {
		if (fabs(segs[i].angle - segs[m-1].angle) > eps)
			segs[m++] = segs[i];
	}
	n = m;
	deq[++rear] = segs[0];
	deq[++rear] = segs[1];
	for (int i = 2; i < n; i++) {
		while (front < rear && cross(segs[i].s, segs[i].e, getIntersect(deq[rear], deq[rear-1])) < -eps)
			rear--;
		while (front < rear && cross(segs[i].s, segs[i].e, getIntersect(deq[front], deq[front+1])) < -eps)
			front++;
		deq[++rear] = segs[i];
	}
	while (front < rear && cross(deq[front].s, deq[front].e, getIntersect(deq[rear], deq[rear-1])) < -eps)
		rear--;  
    while (front < rear && cross(deq[rear].s, deq[rear].e, getIntersect(deq[front], deq[front+1])) < -eps)
    	front++;
	for (int i = front; i < rear; i++) {
		Pt p = getIntersect(deq[i], deq[i+1]);
    	times[deq[i].label].insert(p);
    	times[deq[i+1].label].insert(p);
//    	printf("%lf %lf\n", p.x, p.y);
	}
	if (rear > front + 1) {
		Pt p = getIntersect(deq[front], deq[rear]);
		times[deq[front].label].insert(p);
    	times[deq[rear].label].insert(p);
	}
}
struct Tank {
	double x, v;
	int label;
	Tank(double a = 0, double b = 0, int l = -1):
		x(a), v(b), label(l) {}
	bool operator<(const Tank &other) const {
		if (fabs(x - other.x) > eps)	return x < other.x;
		return v > other.v;
	}
};	
Seg segs[MAXN];
Tank tanks[MAXN];
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
	int n;
	double x, v;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &v);
			tanks[i] = Tank(x, v, i);
			times[i].clear();
		}
		sort(tanks, tanks + n);
		int m = 0;
		for (int i = 0; i < n; i++) {
			if (i && fabs(tanks[i].x - tanks[i-1].x) < eps)
				continue;
			x = tanks[i].x, v = tanks[i].v;
			segs[m++] = Seg(Pt(0, x), Pt(1, x+v), tanks[i].label);			
		}
		segs[m++] = Seg(Pt(0, 1), Pt(0, 0), n);
		halfPlaneIntersect(segs, m);
		
		int one = 0;
		for (int i = 0; i < n; i++)
			one += times[i].size() > 1;
		for (int i = 0; i < n; i++) {
			if (i)	putchar(' ');
			if (one)
				printf("%d", times[i].size() > 1);
			else
				printf("%d", times[i].size() > 0);
		}
		puts("");
	}
	return 0;
}
/*
3
5 -1
1 2
3 -3

6
16 0.125
14 0.2727
18 -0.125
4  0.8333
12 0.3
6  0.5714

3
4 1
4 0.5
0 2.25

4
3 0
5 -1
0 0.75
1 0.5

3
3 -1
2 -0.25
1 -0.5

4
0 1
1 0.75
2 0.5
3 0.25 

10
26 0.38
44 0.14
20 0.46
-6 0.26
-35 0.34
48 0.5
-17 0.44
-29 0.4
1 0.11
-8 0.27

10
-10 0.44
-37 0.3
16 0.42
-3 0.2
1 0.43
-44 0.47
4 0.50
48 0.6
48 0.20
24 0.33

10
7 0.36
31 0.35
1 0.37
36 0.39
32 0.43
37 0.38
-13 0.38
-25 0.0
16 0.36
47 0.11

7 
0.000000 0.000000
-1.000000 1.000000
-3.000000 2.000000
-6.000000 3.000000
-10.000000 4.000000
-15.000000 5.000000
-21.000000 6.000000
*/
