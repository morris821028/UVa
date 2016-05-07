#include <bits/stdc++.h>
using namespace std;

int main() {
	double n;
	while (scanf("%lf", &n) == 1 && n) {
		double n2 = n*2;
		double x_sq = 0, x;
		double avg;
		x_sq = n2 * (n2+1) * (2*n2+1) / 6
			- 4 * (n) * (n+1) * (2*n+1) / 6;
		x = n2 * (n2+1) / 2 - 2 * (n) * (n+1) / 2;
		avg = x * 1.f / n;
		double S = sqrt((x_sq - 2 * avg * x + avg*avg * n) * 1.f/ (n-1));
		printf("%.6lf\n", S);
	}
	return 0;
}

