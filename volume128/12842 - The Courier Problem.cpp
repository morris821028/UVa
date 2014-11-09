#include <stdio.h>
#include <math.h>
int main() {
	int testcase, cases = 0;
	double L;
	double u = 1, v = (-2 + sqrt(8))/ 2.0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf", &L);
		double time = L / v;
		printf("Case %d: %.2lf\n", ++cases, time * u);
	}
	return 0;
}
/*
army v, courier u
time: 
L / v = L / (u - v) + L / (u + v) => u^2 - v^2 = 2v
result L / v * u, let u = 1 => v = (-2 + sqrt(8))/ 2.0.
*/
