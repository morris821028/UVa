#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	double D, V;
	const double pi = acos(-1);
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf", &D, &V);
		V *= 282.0;
		double r = sqrt(V * 3 /(pi * D * 7) * 4);
		printf("Case %d: %.3lf\n", ++cases, r * 2);
	}
	return 0;
}
/*
2
12 25
10 33
*/
