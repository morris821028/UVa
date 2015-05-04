// WTF about check 3D obtuse triangle, 
// use theta = acos(a * b) / |a| / |b|, if a * b > 0, always WA.
// more precision !!!!! 
#include <stdio.h>
#include <math.h>
struct Point3D {
	double x, y, z;
	Point3D(double a = 0, double b = 0, double c = 0):
		x(a), y(b), z(c) {}
	double length() {
		return x * x + y * y + z * z;
	}
	Point3D operator-(const Point3D &other) const {
		return Point3D(x - other.x, y - other.y, z - other.z);
	}
};
const int MAXN = 128;
const double pi = acos(-1);
Point3D A[MAXN], B[MAXN];
int main() {
	const double r = 40000.0 / (2*pi);
	int n, m;
	double x, y, z;
	while (scanf("%d %d", &n, &m) == 2) {
		if (n == 0 && m == 0)
			break;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf", &x, &y, &z);
			A[i] = Point3D(x, y, z);
		}
		for (int i = 0; i < m; i++) {
			scanf("%lf %lf %lf", &x, &y, &z);
			B[i] = Point3D(x, y, z);
		}
		
		int ret = 0;
		for (int i = 0; i < m; i++) {
			int kill = 0;
			for (int j = 0; j < n; j++) {
				double a2 = (A[j] - Point3D(0, 0, 0)).length();
				double b2 = (A[j] - B[i]).length();
				double c2 = r * r;
				if (sqrt(a2 - c2) >= sqrt(b2)) {
					kill = 1;
					break;
				}
			}
			ret += kill;
		}
		printf("%d\n", ret);
	}
	return 0;
}
