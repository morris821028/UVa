#include <stdio.h>
#include <math.h>
using namespace std;

double f[128] = {};
int n;
double g(double val) {
	double ret = 0;
	for (int i = 0; i <= n; i++) {
		ret += f[i] * pow(val, i+1);
	}
	return ret;
}
int main() {
	double l, r;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = n; i >= 0; i--) {
			scanf("%lf", &f[i]);
			f[i] = f[i] / (i+1);
		}
		scanf("%lf %lf", &l, &r);
		printf("%.3lf\n", (g(r) - g(l))/(r - l));
	}
	return 0;
}
