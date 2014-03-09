#include <stdio.h>
#include <math.h>
using namespace std;
int mod0(double a, double b) {
	return fmod(a, b) < 1e-8 || fabs(fmod(a, b) - b) < 1e-8; 
}
int main() {
	double x1, x2, x3;
	double y1, y2, y3;
	const double pi = acos(-1);
	while(scanf("%lf %lf", &x1, &y1) == 2) {
		scanf("%lf %lf", &x2, &y2);
		scanf("%lf %lf", &x3, &y3);
		double a, b, c, ta, tb, tc;
		a = hypot(x1 - x2, y1 - y2);
		b = hypot(x3 - x2, y3 - y2);
		c = hypot(x1 - x3, y1 - y3);
		ta = acos((b*b + c*c - a*a) / (2*b*c));
		tb = acos((a*a + c*c - b*b) / (2*a*c));
		tc = acos((a*a + b*b - c*c) / (2*a*b));
		ta = ta * 2;
		tb = tb * 2;
		tc = tc * 2;
		for(int i = 3; i <= 1000; i++) {
			double theta = 2 * pi / i;
			if(mod0(ta, theta) && mod0(tb, theta) && mod0(tb, theta))
				printf("%d\n", i), i = 1024;
		}
	}
	return 0;
}
