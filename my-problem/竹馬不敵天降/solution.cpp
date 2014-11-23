// simple O(N^2 log N)
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
double calc_convexarea(const vector<Pt> &p) {
    double ret = 0;
    int n = p.size();
    for(int i = 0, j = n - 1; i < n; j = i++)
        ret += p[j].x * p[i].y - p[j].y * p[i].x;
    return fabs(ret /2.0);
}
bool cmp(pair<double, int> a, pair<double, int> b) {
	if (fabs(a.first - b.first) > eps)
		return a.first > b.first;
	return a.second < b.second;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	int n, A, B, cases = 0;
	Pt p[128], mid, vij;
	while (scanf("%d %d %d", &n, &A, &B) == 3) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		vector< pair<double, int> > ret;
		for (int i = 0; i < n; i++) {
			int m = 0;
			vector<Seg> segs;
			segs.resize(n - 1 + 4);
			for (int j = 0; j < n; j++) {
				if (i == j)	continue;
				mid.x = (p[i].x + p[j].x) /2.0;
				mid.y = (p[i].y + p[j].y) /2.0;
				vij.x = mid.x - (p[j].y - p[i].y);
				vij.y = mid.y + (p[j].x - p[i].x);
				segs[m] = Seg(mid, vij), m++;
			}
			segs[m++] = Seg(Pt(0, 0), Pt(A, 0));
			segs[m++] = Seg(Pt(A, 0), Pt(A, B));
			segs[m++] = Seg(Pt(A, B), Pt(0, B));
			segs[m++] = Seg(Pt(0, B), Pt(0, 0));
			vector<Pt> convex = halfPlaneIntersect(segs);
//			for (int j = 0; j < convex.size(); j++)
//				printf("%lf %lf\n", convex[j].x, convex[j].y);
//			puts("--");
			double pp = calc_convexarea(convex) / (A * B);
			ret.push_back(make_pair(pp, i));
		}		
		sort(ret.begin(), ret.end(), cmp);
		printf("Case %d:", ++cases);
		for (int i = 0; i < ret.size(); i++) {
			printf(" %d", ret[i].second + 1);
			printf(" %lf\n", ret[i].first);
		}
		puts("");
	}
	return 0;
}
/*
2 5 3
1 2
4 2

2 5 3
1 1
2 2

3 5 3
1 1
2 2
4 1
*/
