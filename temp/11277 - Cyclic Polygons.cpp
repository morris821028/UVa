#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
const double pi = acos(-1);
double heron(double a, double b, double c) {
	if (a + b < c || b + c < a || c + a < b)
		return 0;
	double s = (a + b + c)/2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}
int main() {
	int testcase, n;
	double A[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		double sum = 0;
		for (int i = 0; i < n; i++)
			scanf("%lf", &A[i]), sum += A[i];
		double l = 0, r = sum, mid = A[0];
		int ok = 1;
		for (int i = 0; i < n; i++)
			l = max(l, A[i]/2);
		if (sum - l * 2 < l * 2)	ok = 0;
		for (int it = 0; it < 40; it++) {
			mid = (l + r)/2;
			double theta = 0;
			for (int i = 0; i < n; i++)
				theta += asin((A[i]/2) / mid) * 2;
			if (theta > 2 * pi)
				l = mid;
			else
				r = mid;
		}
		
		double area = 0, R = mid;
		for (int i = 0; i < n; i++)
			area += heron(R, R, A[i]);
		if (!ok)	area = 0;
		printf("%.3lf\n", area);
	}
	return 0;
}
/*
999
3
3.000
4.000
5.000
5
2 3 4 5 6
3
1 2 4
*/
