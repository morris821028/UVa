#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-7
#define MAXN 32767
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
int halfPlaneIntersect(vector<Seg> segs) {
	sort(segs.begin(), segs.end());
	int n = segs.size(), m = 1;
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
    return front + 1 < rear;
//    vector<Pt> ret;
//	for (int i = front; i < rear; i++) {
//		Pt p = getIntersect(deq[i], deq[i+1]);
//		ret.push_back(p);
//	}
//	if (rear > front + 1) {
//		Pt p = getIntersect(deq[front], deq[rear]);
//		ret.push_back(p);
//	} 
//	return ret;
}
int testRadius(double r, Pt D[], int n) {
	vector<Seg> segs;
	for (int i = 0, j = n-1; i < n; j = i++) {
		Pt a = D[j], b = D[i]; // \vec{ab}
		Pt nab(b.y - a.y, a.x - b.x); // normal vector
		double v = hypot(nab.x, nab.y);
		nab.x = nab.x / v * r, nab.y = nab.y / v * r;
		a = a - nab, b = b - nab;
		segs.push_back(Seg(a, b));
	}
	return halfPlaneIntersect(segs);
}
int main() {
	int n;
	Pt D[128];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &D[i].x, &D[i].y);
		double l = 0, r = 10000, mid, ret;
		while (fabs(l - r) > eps) {
			mid = (l + r)/2;
			if(testRadius(mid, D, n))
				l = mid, ret = mid;
			else
				r = mid;
		}
		printf("%lf\n", ret);
	}
	return 0;
}
/*
4 
0 0 
10000 0 
10000 10000 
0 10000 
3 
0 0 
10000 0 
7000 1000 
6 
0 40 
100 20 
250 40 
250 70 
100 90 
0 70 
3 
0 0 
10000 10000 
5000 5001 
0
*/
