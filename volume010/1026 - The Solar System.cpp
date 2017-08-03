#include <bits/stdc++.h> 
using namespace std;

int main() {
	const double pi = acos(-1);
	int cases = 0;
	double a1, b1, a2, b2, t1, t2, t;
	while (scanf("%lf %lf %lf", &a1, &b1, &t1) == 3 && a1) {
		scanf("%lf %lf %lf", &a2, &b2, &t);
		double t2 = sqrt(t1*t1*a2*a2*a2/a1/a1/a1);
		double c2 = sqrt(a2*a2 - b2*b2);
		t = fmod(t, t2);
		double area = pi*a2*b2*(t/t2);
		
		double l = 0, r = 2*pi;
		for (int it = 0; it < 100; it++) {
			double theta = (l+r)/2;
			double tmp = theta*a2*b2/2 - b2*c2*sin(theta)/2;
			
			if (tmp < area)
				l = theta;
			else
				r = theta;
		}
		printf("Solar System %d: %.3lf %.3lf\n", ++cases, a2*cos(l), b2*sin(l));
	}
	return 0;
}
/*
10 5 10 10 5 10
10 5 10 20 10 10
*/

