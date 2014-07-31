#include <stdio.h>
#include <math.h>

int main() {
#define eps 1e-6
	int n, m, cases = 0;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		double row[128] = {}, col[128] = {};
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				double x;
				scanf("%lf", &x);
				row[i] += x, col[j] += x;
			}
		}
		double left = 0, right = 0;
		double diff = 1e+30;
		int cx, cy;
		for(int i = 1; i < n; i++)
			right += row[i];
		for(int i = 0; i < n; i++) {
			if(fabs(right - left) < diff + eps) {
				diff = fabs(right - left);
				cx = i;
			}
			left += row[i], right -= row[i+1];
		}
		left = right = 0;
		diff = 1e+30;
		for(int i = 1; i < m; i++)
			right += col[i];
		for(int i = 0; i < m; i++) {
			if(fabs(right - left) < diff + eps) {
				diff = fabs(right - left);
				cy = i;
			}
			left += col[i], right -= col[i+1];
		}
		printf("Case %d: center at (%d, %d)\n", ++cases, cx+1, cy+1);
	}
	return 0;
}
