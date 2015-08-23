#include <bits/stdc++.h> 
using namespace std;

int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		double x[128], y[128], area = 0;
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &x[i], &y[i]);
		for (int i = 0; i < N; i++)
			area += x[i]*y[(i+1)%N] - x[(i+1)%N]*y[i];
		printf("%.2lf\n", fabs(area)/2);
	}
	return 0;
}
