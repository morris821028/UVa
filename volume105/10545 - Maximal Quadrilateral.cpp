#include <stdio.h>
#include <math.h>
// http://en.wikipedia.org/wiki/Brahmagupta%27s_formula
int main() {
	scanf("%*d");
	int cases = 0;
	double p, a, b;
	while(scanf("%lf %lf %lf", &p, &a, &b) == 3) {
		printf("Case %d: ", ++cases);
		if (a > p - a || b > p - b) {
			puts("Eta Shombhob Na.");
			continue;
		}
		double c = p/2 - a;
		double d = p/2 - b;
		printf("%.6f\n", sqrt(a * b * c * d) * 2 / (a + b + c + d));
	}
	return 0;
}
