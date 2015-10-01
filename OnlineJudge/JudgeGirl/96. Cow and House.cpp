#include <stdio.h>

int main() {
	double a, b, c;
	const double pi = 3.1415926; 
	while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
		double ret = 0;
		ret = c*c*pi*0.75;
		if (c >= a)	
			ret += (c-a)*(c-a)*pi/4;
		if (c >= b)	
			ret += (c-b)*(c-b)*pi/4;
		printf("%.6f\n", ret);
	}
	return 0;
}
