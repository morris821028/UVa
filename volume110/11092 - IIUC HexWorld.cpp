#include <bits/stdc++.h>
using namespace std;

pair<double, double> hex_loc(int x) {
	static const double sqr3 = sqrt(3);
	double cx = 0, cy = 0;
	int i;
	for (i = 0; ; i++) {
		if (x <= i*6)
			break;
		cx += 0.5, cy -= sqr3/2;
		x -= i*6;
	}
	if (x == 0)
		return {cx, cy};
	x--, cx += 0.5, cy += sqr3/2;
	if (x < i) {
		cx += x*0.5, cy += x*sqr3/2;
		return {cx, cy};
	}
	x -= i, cx += (i-2)*0.5, cy += i*sqr3/2;
	if (x < i) {
		cx -= x*0.5, cy += x*sqr3/2;
		return {cx, cy};
	}
	x -= i, cx -= (i-1)*0.5+1, cy += (i-1)*sqr3/2;
	if (x < i) {
		cx -= x;
		return {cx, cy};
	}
	x -= i, cx -= (i-0.5), cy -= sqr3/2;
	if (x < i) {
		cx -= x*0.5, cy -= x*sqr3/2;
		return {cx, cy};
	}
	x -= i, cx -= (i*0.5-1), cy -= (i)*sqr3/2;
	if (x < i) {
		cx += x*0.5, cy -= x*sqr3/2;
		return {cx, cy};
	}
	x -= i, cx += (i-1)*0.5+1, cy -= (i-1)*sqr3/2;
	cx += x;
	return {cx, cy};
} 

double hex_distance(int A, int B) {
	pair<double, double> la = hex_loc(A), lb = hex_loc(B);
	return hypot(la.first-lb.first, la.second-lb.second);
}

int main() {
//	for (int i = 0; i <= 18; i++) {
//		auto v = hex_loc(i);
//		printf("[%d] %lf %lf\n", i, v.first, v.second);
//	}
	int A, B;
	while (scanf("%d %d", &A, &B) == 2) {
		double d1 = fabs(A-B), d2 = hex_distance(A, B);
		printf("%.3lf %.3lf\n", d1, d2);
	}
	return 0;
}
