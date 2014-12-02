#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

struct Point3D {
	double x, y, z;
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
	double dist(Point3D a) {
		return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2) + pow(a.z - z, 2));
	}
};
int main() {
	const double pi = acos(-1);
	int n, A[10], cases = 0;
	Point3D L, R, D[10];
	while (scanf("%d", &n) == 1 && n) {
		L.read();
		R.read();
		for (int i = 0; i < n; i++)
			D[i].read();
		for (int i = 0; i < n; i++)
			A[i] = i;
		double ret = 0;
		do {
			double r[10], V = 0;
			for (int i = 0; i < n; i++) {
				double pr = 1e+30;
				pr = min(pr, fabs(D[A[i]].x - L.x));
				pr = min(pr, fabs(D[A[i]].x - R.x));
				pr = min(pr, fabs(D[A[i]].y - L.y));
				pr = min(pr, fabs(D[A[i]].y - R.y));
				pr = min(pr, fabs(D[A[i]].z - L.z));
				pr = min(pr, fabs(D[A[i]].z - R.z));
				for (int j = 0; j < i; j++) {
					double t = D[A[i]].dist(D[A[j]]);
					pr = min(pr, t - r[A[j]]);
				}
				r[A[i]] = pr < 0 ? 0 : pr;
				V += 4/3.0 * pi * pow(r[A[i]], 3);
			}
			ret = max(ret, V);
		} while (next_permutation(A, A+n));
		
		double totV = fabs((L.x - R.x) * (L.y - R.y) * (L.z - R.z));
		printf("Box %d: %.0lf\n\n", ++cases, totV - ret);
	}
	return 0;
}
