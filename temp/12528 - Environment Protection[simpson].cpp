#include <stdio.h>
#include <math.h>
#include <algorithm> 
using namespace std;
int W, D, A, K;
double P1[16], P2[16], Q1[16], Q2[16];
double calc(double x, double base) {
	double vp1, vp2, vq1, vq2, y1, y2;
	vp1 = vp2 = vq1 = vq2 = 0;
	for (int j = K; j >= 0; j--) {
		vp1 = vp1 * x + P1[j];
		vp2 = vp2 * x + P2[j];
		vq1 = vq1 * x + Q1[j];
		vq2 = vq2 * x + Q2[j];
	}
	y1 = vp1 / vq1, y2 = vp2 / vq2;
	if (y1 < base)	return 0;
	if (y2 > base)	return y1 - y2;
	return y1 - base;
}
int main() {
	while (scanf("%d %d %d %d", &W, &D, &A, &K) == 4) {
		for (int i = 0; i <= K; i++)	scanf("%lf", &P1[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &Q1[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &P2[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &Q2[i]);
		
		double l = -D, r = 0, mid = D;
#define eps 1e-5
#define eps2 1e-4
		for (int it = 0; it < 22; it++) {
			mid = (l + r)/2;
			double sum = 0, fa, fb, fab2;
			for (double a = 0, b = eps2; a + eps2 - eps < W; a += eps2, b = a + eps2)
				sum += (b - a) / 6 * (calc(a, mid) + 4 * calc((a + b)/2, mid) + calc(b, mid));
			if (sum < A)
				r = mid;
			else
				l = mid;
		}
		printf("%.5lf\n", - l);
	}
	return 0;
}
/*
6 9 4 1
-10 1
2 0
-16 1
2 0

8 10 14 4
-1392 864 -216 24 -1
1312 -864 216 -24 1
-73 36 -54 36 -9
17 -4 6 -4 1
*/
