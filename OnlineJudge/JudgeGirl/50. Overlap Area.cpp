#include <stdio.h>
#include <limits.h>
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
void inter(int x1[], int y1[], int x2[], int y2[], int xr[], int yr[]) {
	xr[0] = max(x1[0], x2[0]), xr[1] = min(x1[1], x2[1]);
	yr[0] = max(y1[0], y2[0]), yr[1] = min(y1[1], y2[1]);
}
int area(int x[], int y[]) {
	if (x[0] > x[1] || y[0] > y[1])	return 0;
	return (x[1]-x[0])*(y[1]-y[0]);
}
int main() {
	int x[3][2], y[3][2];
	int n = 3, ret = 0;
	for (int i = 0; i < n; i++)
		scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
	for (int i = 1; i < (1<<n); i++) {
		int xr[2]  = {INT_MIN, INT_MAX}, yr[2] = {INT_MIN, INT_MAX};
		int cc = 0;
		for (int j = 0; j < n; j++) {
			if ((i>>j)&1)
				inter(xr, yr, x[j], y[j], xr, yr), cc++;
		}
		if (cc&1)	ret += area(xr, yr);
		else		ret -= area(xr, yr);
	}
	printf("%d\n", ret);
	return 0;
}
