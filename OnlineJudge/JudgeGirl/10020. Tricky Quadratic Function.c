#include <stdio.h>
#include <math.h>
#include <stdbool.h>
typedef double Float;
bool Quadratic(Float A, Float B, Float C, 
					Float *t0, Float *t1) {
	Float discrim = B*B - 4.f*A*C;
	if (discrim < 0.)	return false;
	Float rootDiscrim = sqrt(discrim), q;
	if (B < 0)	q = -.5f*(B - rootDiscrim);
	else		q = -.5f*(B + rootDiscrim);
	*t0 = q / A;
	*t1 = C / q;
	if (*t0 > *t1) {
		Float t;
		t = *t0, *t0 = *t1, *t1 = t;
	}
	return true;
}
int main() {
	Float a, b, c;
	while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
		Float t0, t1;
		bool f = Quadratic(a, b, c, &t0, &t1);
		printf("%.20lf %.20lf\n", t0, t1);
	}
	return 0;
}


