// wrong answer
#include <stdio.h>
#include <math.h>
#include <algorithm> 
using namespace std;
#define MAXN 131072

double f1[MAXN], f2[MAXN];
int main() {
	int W, D, A, K;
	while (scanf("%d %d %d %d", &W, &D, &A, &K) == 4) {
		double P1[16], P2[16], Q1[16], Q2[16];
		for (int i = 0; i <= K; i++)	scanf("%lf", &P1[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &Q1[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &P2[i]);
		for (int i = 0; i <= K; i++)	scanf("%lf", &Q2[i]);
		double dx = (double) W / MAXN;
		for (int i = 0; i < MAXN; i++) {
			double x = (i + 1) * dx;
			double vp1, vp2, vq1, vq2;
			vp1 = vp2 = vq1 = vq2 = 0;
			for (int j = K; j >= 0; j--) {
				vp1 = vp1 * x + P1[j];
				vp2 = vp2 * x + P2[j];
				vq1 = vq1 * x + Q1[j];
				vq2 = vq2 * x + Q2[j];
			}
			f1[i] = vp1 / vq1, f2[i] = vp2 / vq2;
		}
		
		double l = -D, r = 0, mid = D;
#define eps 1e-5
		for (int it = 0; it < 22; it++) {
			mid = (l + r)/2;
			double sum = 0;
			for (int i = 0; i < MAXN - 1; i++) {
				sum += max(f1[i], mid) - max(f2[i], mid) + max(f1[i+1], mid) - max(f2[i+1], mid);
			}
			sum = sum * dx / 2;
			if (sum > A)
				l = mid;
			else
				r = mid;
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
