#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const double pi = acos(-1);
int main() {
	int N;
	double R, theta[512];
	while (scanf("%d %lf", &N, &R) == 2 && N) {
		for (int i = 0; i < N; i++) {
			scanf("%lf", &theta[i]);
			theta[i] = theta[i] * pi / 180;
		}
		sort(theta, theta+N);
		double ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				int a = j - i - 1;
				int b = N - a - 2;
				double A, B, t = theta[j] - theta[i];
				A = t /2 * R * R - R * R * sin(t)/2;
				B = R * R * pi - A;
				ret += a * B + b * A;
//				printf("[%lf %lf] %lf %lf\n", theta[i], theta[j], A, B);
			}
		}
		ret = (double)(N) * (N-1) * (N-2) / 6 * R * R * pi - ret;
		if (N < 3)	ret = 0;
		printf("%.0lf\n", ret);
	}
	return 0;
}
/*
5 10
10.00
100.00
300.00
310.00
320.00
3 20
10.00
100.00
300.00
0 0
*/
