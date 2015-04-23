#include <stdio.h>

double isValid(int N, double H1, double H2) {
	double H = 0;
	for (int i = 3; i <= N; i++) {
		H = 2 * H2 + 2 - H1;
		if (H < 0)	return -1;
		H1 = H2;
		H2 = H;
	}
	return H;
}
int main() {
	int N;
	double A;
	while (scanf("%d %lf", &N, &A) == 2) {
		double l = 0, r = A, mid, ret = 0, t;
		for (int it = 0; it < 50; it++) {
			mid = (l + r)/2;
			if ((t = isValid(N, A, mid)) >= 0)
				r = mid, ret = t;
			else
				l = mid;
		}
		printf("%.2lf\n", ret);
	}
	return 0;
}
