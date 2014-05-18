#include <stdio.h>
#include <math.h>

int main() {
	scanf("%*d");
	double x, y, r;
	while(scanf("%lf %lf %lf", &x, &y, &r) == 3) {
		printf("%.2lf %.2lf\n", r - hypot(x, y), r + hypot(x, y));
	}
	return 0;
}
