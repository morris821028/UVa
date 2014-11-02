#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int n, x[128], y[128], z[128], r[128];
	int cases = 0;
	while (scanf("%d", &n) == 1 && n >= 0) {
		for (int i = 0; i < n + 2; i++) {
			if (i < n)
				scanf("%d %d %d %d", &x[i], &y[i], &z[i], &r[i]);
			else
				scanf("%d %d %d", &x[i], &y[i], &z[i]), r[i] = 0;			
		}
		n += 2;
		double f[128][128];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)	f[i][i] = 0;
				else {
					double dist = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2) + pow(z[i] - z[j], 2));
					if (dist <= r[i] + r[j])
						f[i][j] = 0;
					else
						f[i][j] = dist - (r[i] + r[j]);
				}
			}
		}
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		printf("Cheese %d: Travel time = %.0lf sec\n", ++cases, f[n-1][n-2] * 10);
	}
	return 0;
}
