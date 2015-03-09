#include<stdio.h>
double a, b, c, d;
double calu(double x) {
	return a*x*x*x + b*x*x + c*x + d;
}
void test() {
	int i = -100000, j = 100000;
	for(; i <= j; i++) {
		double f1 = calu(i/1000.0), f2 = calu((i-1)/1000.0);
		if(f1 * f2 <= 0)
			printf("%.2lf ", i/1000.0), i+= 1000;
	}
	puts("");
}
main() {
	while(scanf("%lf %lf %lf %lf", &a, &b, &c, &d) == 4) {
		test();
	}
	return 0;
}
