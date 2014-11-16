#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define eps 1e-9
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
int testBlowUp(int m, Pt D[], int n) {
	vector<Seg> segs;
	for (int i = 0; i < n; i++) {
		Pt a = D[i], b = D[i + m];
		segs.push_back(Seg(b, a));
	}
	return halfPlaneIntersect(segs);
}
Pt D[131072];
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &D[i].x, &D[i].y);
			D[i + n] = D[i];
		}
		if (n <= 3) {
			puts("1");
			continue;
		}
		int l = 1, r = n - 2, mid, ret;
		while (l <= r) {
			mid = (l + r)/2;
			if(testBlowUp(mid, D, n))
				l = mid + 1, ret = mid;
			else
				r = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3 
0 0 
50 50 
60 10 
5 
0 0 
0 10 
10 20 
20 10 
25 0
*/
