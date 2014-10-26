#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

struct Point3D {
	double x, y, z;
	Point3D(double a = 0, double b = 0, double c = 0):
		x(a), y(b), z(c) {}
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
	Point3D operator+(const Point3D &a) const {
		return Point3D(x + a.x, y + a.y, z + a.z);
	}
	Point3D operator-(const Point3D &a) const {
		return Point3D(x - a.x, y - a.y, z - a.z);
	}
	Point3D operator/(const double &a) const {
		return Point3D(x/a, y/a, z/a);
	}
	Point3D operator*(const double &a) const {
		return Point3D(x*a, y*a, z*a);
	}
	double dist(Point3D a) const {
		return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y) + (z - a.z) * (z - a.z));
	}
	double dist2(Point3D a) const {
		return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y) + (z - a.z) * (z - a.z);
	}
};
int main() {
	int testcase, cases = 0;
	double time;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf", &time);
		Point3D A, B, C, D, V1, V2;
		A.read(), B.read();
		C.read(), D.read();
		V1 = (B - A) / time;
		V2 = (D - C) / time;
		double l = 0, r = 1e+8;
		double mid, midmid, md, mmd;
		double mndist = A.dist2(C);
		while (fabs(l - r) > 1e-8) {
			mid = (l + r)/2;
			midmid = (mid + r)/2;
			md = ((V1 * mid) + A).dist2((V2 * mid) + C);
			mmd = ((V1 * midmid) + A).dist2((V2 * midmid) + C);
			mndist = min(mndist, md);
			mndist = min(mndist, mmd);
			if (md < mmd)
				r = midmid;
			else
				l = mid;
		}
		printf("Case %d: %.4lf\n", ++cases, sqrt(mndist));
	}
	return 0;
}
