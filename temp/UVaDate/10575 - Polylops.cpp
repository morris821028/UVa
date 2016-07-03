#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>
#include <vector>
#include <string.h>
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
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Pt &a) const {
    	return !(a == *this);
	}
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	double length() {
		return hypot(x, y);
	}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
};
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
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
int test(Pt D[], int N, Pt mid, Pt nab, int p, int q) {
	Pt u;
	for (int i = 0; i < N; i++) {
		u = (D[p] + D[q])*0.5;
		if (cmpZero(cross(mid, mid+nab, u)))
			return 0;
		if (cmpZero(dot(nab, D[p] - D[q])))
			return 0;
		p = (p+1)%N, q = (q+N-1)%N;
	}
	return 1;
}
int main() {
	int cases = 0;
	int N;
	Pt D[1024];
	while (scanf("%d", &N) == 1 && N) {
		map<Pt, int> R;
		for (int i = 0; i < N; i++)
			D[i].read(), R[D[i]] = i;
		
		int ret = 0;
		set<double> S;
		for (int i = 0; i < N; i++) {
			Pt a, b, mid, nab;
			a = D[i], b = D[(i+1)%N];
			mid = (a + b)*0.5;
			nab.x = a.y - b.y, nab.y = b.x - a.x;
			if (nab.x < 0 || (nab.x == 0 && nab.y < 0))
				nab.x = -nab.x, nab.y = -nab.y;
			if (!S.count(atan2(nab.y, nab.x))) {
				if (test(D, N, mid, nab, i, (i+1)%N))
					S.insert(atan2(nab.y, nab.x));				
			}
			
			a = D[i], b = D[(i+2)%N];
			mid = (a + b)*0.5;
			nab.x = a.y - b.y, nab.y = b.x - a.x;
			if (nab.x < 0 || (nab.x == 0 && nab.y < 0))
				nab.x = -nab.x, nab.y = -nab.y;
			if (!S.count(atan2(nab.y, nab.x))) {
				if (test(D, N, mid, nab, i, (i+2)%N))
					S.insert(atan2(nab.y, nab.x));				
			}
		}
		ret = (int) S.size();
		printf("Polygon #%d has %d symmetry line(s).\n", ++cases, ret);
	}
	return 0;
}
