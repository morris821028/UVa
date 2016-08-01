#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const double pi = acos(-1);
struct Hole {
	double x, y, z, r;
	void unit() {
		x /= 1000.0, y /= 1000.0, z /= 1000.0, r /= 1000.0;
	}
	double V() {
		return r*r*r*pi*4.0/3;
	}
	bool operator<(const Hole &a) const {
		return z < a.z;
	}
	bool intersect(double tl, double tr) {
		return max(tl, z-r) < min(tr, z+r);
	}
	double f(double x) {
		return (r*r*x - x*x*x/3)*pi;
	}
	double partial(double tl, double tr) {
		tl = max(tl, z-r), tr = min(tr, z+r);
		double a = tl - z, b = tr - z;
		if (a >= 0)
			return f(b) - f(a);
		if (b <= 0)
			return f(-a) - f(-b);
		return f(b) + f(-a);
	}
} H[MAXN];
int main() {
	int N, S;
	while (scanf("%d %d", &N, &S) == 2) {
		double V = 100.0*100.0*100.0;
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf %lf %lf", &H[i].r, &H[i].x, &H[i].y, &H[i].z);
			H[i].unit();
			V -= H[i].V();
		}
		V /= S;
		double lz = 0;
		for (int i = 0; i < S; i++) {
			double l = lz, r = 100, mid;
			for (int it = 0; it < 100 && fabs(l - r) > 1e-9; it++) {
				mid = (l + r)/2;
				double vs = (mid - lz)*100.0*100.0;
				for (int j = 0; j < N && vs > V; j++) {
					if (H[j].intersect(lz, mid)) {
						vs -= H[j].partial(lz, mid);
					}
				}
				if (vs < V)
					l = mid;
				else
					r = mid;
			}
			printf("%.9lf\n", mid-lz);
			lz = mid;
		}
	}
	return 0;
}
/*
0 4
2 5
10000 10000 20000 20000
40000 40000 50000 60000
*/
