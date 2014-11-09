#include <stdio.h>
#include <math.h>

int main() {
	int testcase, cases = 0;
	const double pi = acos(-1);
	double D, N, A; 
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf", &D, &N);
		A = D / (N - 1);
		double ret = 2 * pi * (A + D);
		printf("Case %d: %.3lf\n", ++cases, ret);
	}
	return 0;
}
