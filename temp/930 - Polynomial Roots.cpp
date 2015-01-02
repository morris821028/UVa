#include <stdio.h> 
#include <math.h>

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		double A[128] = {}, x;
		for (int i = n; i >= 0; i--)
			scanf("%lf", &A[i]);
		for (int i = 0; i < n-2; i++) {
			scanf("%lf", &x);
			
			double prev = A[n];
			for (int j = n - 1; j >= 0; j--)
				A[j] += prev * x, prev = A[j];
		}
		
		double a = A[n], b = A[n-1], c = A[n-2];
		double r1, r2;
		r1 = (-b + sqrt(b * b - 4 * a * c)) / 2.0 / a;
		r2 = (-b - sqrt(b * b - 4 * a * c)) / 2.0 / a;
		printf("%.1lf\n%.1lf\n", r1, r2);
	}
	return 0;
}
