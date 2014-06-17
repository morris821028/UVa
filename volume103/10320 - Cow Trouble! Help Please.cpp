#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	double w, l, r;
	const double pi = acos(-1);
	while(scanf("%lf %lf %lf", &l, &w, &r) == 3) {
		if(w > l)
			swap(w, l);
		double area;
		if(r <= w)
			area = r * r * pi * 3 / 4.0;
		else if(r <= l)
			area = r * r * pi * 3 / 4.0 + (r - w) * (r - w) * pi / 4.0;
		else if(r <= l + w)
			area = r * r * pi * 3 / 4.0 + (r - w) * (r - w) * pi / 4.0 
					+ (r - l) * (r - l) * pi / 4.0;
		else {
			double a = atan2(l, w), b, c;
			double la, lb, lc;
			
			la = hypot(w, l);
			lb = r - w;
			lc = r - l;
			b = acos((la*la + lb*lb - lc*lc)/(2*la*lb)) + a;
			c = acos((la*la + lc*lc - lb*lb)/(2*la*lc)) + (pi /2) - a;
						
			area = r * r * pi * 3 / 4.0;
			area += (r - w) * (r - w) * (pi - b) / 2;
			area += (r - l) * (r - l) * (pi - c) / 2;
			area += lb * la * sin(b - a) / 2;
			area -= w * l / 2;
		}
		printf("%0.10lf\n", area);			
	}
	return 0;
}
