#include <stdio.h> 
#include <math.h>
// uniformly distributed over the range t .. 1
double calcExpected(int n, double t) {
	double f = pow(2, n);
	double eq, prize;
	for (int i = n - 1; i >= 0; i--) {
		prize = pow(2, i);
		eq = prize / f;
		if (eq <= t)
			f = (t + 1)/2 * f;
		else
			f = (eq - t)/(1 - t) * prize + 
				(1 - eq)/(1 - t) * (eq + 1)/2 * f;
	}
	return f;
}
int main() {
	int n;
	double t;
	while (scanf("%d %lf", &n, &t) == 2 && n) {
		printf("%.3lf\n", calcExpected(n, t));
	}
	return 0;
}
