#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
double mrandom() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int main() {
	int n, a, b, c;
	int cases = 0;
	int x[32], y[32], z[32];
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d %d %d", &a, &b, &c);
		const int runtime = 8000000;
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &x[i], &y[i], &z[i]);
		int count[32] = {}, guess = runtime / n;
		double tx, ty, tz;
		for (int i = guess - 1; i >= 0; i--) {
			tx = mrandom() * a, ty = mrandom() * b, tz = mrandom() * c;
			double dist = 1e+60, tmp;
			int mn = 0;
			for (int j = 0; j < n; j++) {
				tmp = (tx - x[j]) * (tx - x[j]) + (ty - y[j]) * (ty - y[j]) + 
							(tz - z[j]) * (tz - z[j]);
				if (tmp < dist)
					dist = tmp, mn = j;
			}
			count[mn]++;
		}
		printf("Case %d:", ++cases);
		for (int i = 0; i < n; i++)
			printf(" %.3lf", (double) count[i] / guess);
		puts("");		
	}
	return 0;
}
