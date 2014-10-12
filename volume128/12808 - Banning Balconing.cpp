#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	double L, D, H, V;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf %lf %lf", &L, &D, &H, &V);
		L /= 1000;
		D /= 1000;
		H /= 1000;
		V /= 1000;
		double t = sqrt(H * 2 / 9.8), d = V * t;
		if (fabs(d - D) < 0.5 || fabs(d - (D + L)) < 0.5)
			puts("EDGE");
		else if (d < D || d > D + L)
			puts("FLOOR");
		else
			puts("POOL");
	}
	return 0;
}
