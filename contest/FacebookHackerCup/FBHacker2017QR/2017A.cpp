#include <bits/stdc++.h>
using namespace std;

int main() {
	const double eps = 1e-8;
	const double pi = acos(-1);
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int P, X, Y;
		scanf("%d %d %d", &P, &X, &Y);
		int ret = 0;
		
		if (X == 50 && Y == 50) {
			ret = 1;
		} else if (hypot(X-50, Y-50) > 50) {
		} else if (P == 100) {
			ret = 1;
		} else if (P == 0) {
			
		} else {
			int vx = X-50, vy = Y-50;
			int tx = 0, ty = 50;
			double theta = acos((vx*tx+vy*ty)/hypot(vx, vy)/hypot(tx, ty));
			if (tx*vy - ty*vx > 0)
				theta = 2*pi-theta;
			double t = (double) P/100.0*2*pi;
			if (theta <= t)
				ret = 1;
		}
		printf("Case #%d: %s\n", ++cases, ret ? "black" : "white");
	}
	return 0;
}
/*
5000
84 45 93
25 96 50
*/
