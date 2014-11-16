#include <stdio.h> 
#include <algorithm>
using namespace std;
double dfs(double H, double V, double h, double v, double x, double y, int c) {
	double mx, my;
	mx = H * h, my = V * v;
	if (x <= mx && y >= my)	return c; // upper left
	if (x >= mx && y <= my)	return c; // lower right
	if (x <= mx) 	// lower left
		return dfs(H * h, V * v, h, v, x, y, !c);
	else			// upper right
		return dfs(H * (1 - h), V * (1 - v), h, v, x - mx, y - my, !c);
}
int main() {
	double H, V, h, v, x, y;
	int n, cases = 0;
	while (scanf("%lf %lf %lf %lf", &H, &V, &h, &v) == 4 && H) {
		scanf("%d", &n);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			int ret = dfs(H, V, h, v, x, y, 1);
			puts(ret ? "black" : "white");
		}
	}
	return 0;
}
