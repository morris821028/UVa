#include <stdio.h> 
#include <math.h>
using namespace std;

/*
	x^2 / a^2 + y^2 / b^2 = 1 
		area = ab pi
	
	x^2 / a^2 + y^2 / b^2 + z^2 / c^2 = 1
	
	x^2 / (a \sqrt{1 - z^2 / c^2})^2 + y^2 / (b \sqrt{1 - z^2 / c^2})^2 = 1;
	cross-sectional area = ab (1 - z^2 / c^2) pi
	
	volume 	ab (1 - z^2 / c^2) pi dz
			ab pi (z - z^3 / 3 / c^2), for z in [l, r]
*/
const double pi = acos(-1);
int main() {
	int a, b, c, ra, rb, rc;
	int cases = 0;
	while (scanf("%d %d %d %d %d %d", &ra, &rb, &rc, &a, &b, &c) == 6) {
		printf("Set #%d\n", ++cases);
		double ta, tb, tc, l, r;
		if (ra > a || rb > b || rc > c) {
			printf("%.6lf\n", 0.0); // WTF
			continue;
		}
		if (ra < a) {
			ta = b/2.0, tb = c/2.0, tc = a/2.0;
			r = a/2.0, l = r - fabs(a - ra);
		} else if (rb < b) {
			ta = a/2.0, tb = c/2.0, tc = b/2.0;
			r = b/2.0, l = r - fabs(b - rb);
		} else if (rc < c) {
			ta = a/2.0, tb = b/2.0, tc = c/2.0;
			r = c/2.0, l = r - fabs(c - rc);
		} else {
			printf("%.6lf\n", 0.0); // WTF
			continue;
		}
		double area;
		area = ta * tb * pi * (1 - l*l/tc/tc);
		printf("%.6lf\n", area);
	}
	return 0;
}
/*
7 6 4 8 6 4
4 8 8 8 8 8
2 6 4 8 6 4
8 6 4 8 6 4
*/
