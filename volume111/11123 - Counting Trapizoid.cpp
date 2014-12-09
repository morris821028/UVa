#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <assert.h>
using namespace std;

#define eps 1e-9
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
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
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
		if (cross(other.s, other.e, s) > eps)
			return true;
		return false;
	}
};
struct DOUBLE {
	double v;
	DOUBLE(double a = 0):
		v(a) {}
	bool operator<(const DOUBLE &other) const {
		if (fabs(v - other.v) > eps)
			return v < other.v;
		return false;
	}
};
Pt D[256];
Seg segs[65536], buf[65536];

int main() {
	int cases = 0;
	int n, m;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &D[i].x, &D[i].y);
		sort(D, D + n);
		
		m = 0;
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++)
				segs[m++] = Seg(D[i], D[j]);
		
		sort(segs, segs + m);
		long long ret = 0;
		for (int i = 0; i < m; ) {
			int j = i, tn = 0;
			while (j < m && fabs(segs[i].angle - segs[j].angle) < eps)
				buf[tn++] = segs[j], j++;
			i = j;
			
			map<DOUBLE, int> LEN; // LEN[len] = count.
			queue<Seg> Q;
			int tmp = 0;
//			for (int k = 0; k < tn; k++)
//				printf("(%lf %lf) - (%lf %lf)\n", buf[k].s.x, buf[k].s.y, buf[k].e.x, buf[k].e.y);
//			puts("--- same slope");
			for (int k = 0; k < tn; k++) {
				while (!Q.empty() && fabs(cross(buf[k].s, buf[k].e, Q.front().s)) > eps) {
					Seg t = Q.front();
					Q.pop();
					tmp++, LEN[DOUBLE(dist(t.s, t.e))]++;
				}
				int comb = tmp - LEN[DOUBLE(dist(buf[k].s, buf[k].e))]; // remove same length
				ret += comb;
				Q.push(buf[k]);
			}
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
4
0 0
1 0
0 1
1 1

4
0 0
1 1
2 0
0 1

6
5 1
3 1
5 0
3 3
2 4
0 8



0
*/
