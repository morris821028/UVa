#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-10
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
vector<Pt> halfPlaneIntersect(vector<Seg> segs) {
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
    vector<Pt> ret;
	for (int i = front; i < rear; i++) {
		Pt p = getIntersect(deq[i], deq[i+1]);
		ret.push_back(p);
	}
	if (rear > front + 1) {
		Pt p = getIntersect(deq[front], deq[rear]);
		ret.push_back(p);
	} 
	return ret;
}
double calcArea(vector<Pt> p) {
	double ret = 0;
	int n = p.size();
	if(n < 3) return 0.0;
	for(int i = 0, j = n-1; i < n; j = i++)
		ret += p[i].x * p[j].y - p[i].y * p[j].x;
	return fabs(ret)/2;
}
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
void formalOrder(vector<Pt> &A) { // to counter-clockwise
	int s = 0, n = (int) A.size();
	for (int i = 0; i < A.size(); i++)
		if (A[i] < A[s])
			s = i;
	if (cmpZero(cross(A[(s+n-1)%n], A[s], A[(s+1)%n])) < 0)
		reverse(A.begin(), A.end());
}
int main() {
	int testcase;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		vector<Pt> D;
		vector<Seg> segs;
		for (int i = 0; i < n; i++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			D.push_back(Pt(x, y));
		}
		
		formalOrder(D);
		for (int i = 0; i < n; i++)
			segs.push_back(Seg(D[i], D[(i+1)%n]));
			
		vector<Pt> convex = halfPlaneIntersect(segs);
		double ret = calcArea(convex);
		printf("%.2lf\n", ret);
	}
	return 0;
}
