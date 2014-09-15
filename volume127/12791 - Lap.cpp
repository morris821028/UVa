#include <stdio.h> 
#include <math.h>

int main() {
	int X, Y;
	while (scanf("%d %d", &X, &Y) == 2) {
		double l = 0, r = 1e+30, mid;
		int ret = 0;
#define eps 1e-8
		while (fabs(l - r) > eps) {
			mid = (l + r)/2;
			if (mid * (1.0/X - 1.0/Y) >= 1)
				r = mid;
			else
				l = mid;
		}
		printf("%.0lf\n", ceil(mid/X));
	}
	return 0;
}
/*
1 10
4 8
5 7
6875 7109
*/
