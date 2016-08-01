#include <stdio.h> 
#include <math.h>
// perfect median
// https://oeis.org/A001109
// a(n) = 6*a(n-1) - a(n-2)
// 0, 1, 6, 35, 204, 1189, 6930, 40391, 235416
int main() {
//	long long al = 1, ar = 1, asum = 1;
//	long long bl = 3, br = 3, bsum = 3;
//	for (int center = 2; center < 10000; center++) {
//		while (bsum < asum)
//			br++, bsum += br;
//		if (asum == bsum) {
//			printf("%d\n", center);
//		}
//		ar = center, asum += center;
//		bsum -= bl, bl++;
//	}
//	long long A[30] = {0, 1};
//	for (int i = 2; i < 25; i++) {
//		A[i] = A[i-1] * 6 - A[i-2];
//		long long k = (- (2 * A[i] + 1) + sqrt(8 * A[i] * A[i] + 1))/2;
//	}
	long long B[30] = {0, 1};
	for (int i = 2; i < 25; i++)
		B[i] = B[i-1] * 6 - B[i-2] + 2;
	long long n;
	while (scanf("%lld", &n) == 1 && n) {
		int ret = 0;
		for (int i = 2; i < 25 && B[i] <= n; i++)
			ret++;
		printf("%d\n", ret);
	}
	return 0;
}
