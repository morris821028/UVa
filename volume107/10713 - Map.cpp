#include <stdio.h>
#include <math.h> 
#define eps 1e-8 
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	double r, x1, x2, y1, y2;
	const double sq2 = sqrt(2);
	int cases = 0;
	while(scanf("%lf %lf %lf %lf %lf", &r, &x1, &y1, &x2, &y2) == 5) {
		if(cases++)	puts("");
		double dx = x2 - x1, dy = y2 - y1;
		if(fabs(dx) < fabs(dy)) {
			double diff = fabs(dy) - fabs(dx);
			if(dy < 0) {
				double x = x1 + dx, y = y1 - fabs(dx);
//				printf("%lf %lf\n", x, y);
				if(x*x + y*y > r*r) {
					if(fabs(diff) > eps)
						printf("south %.10lf\n", diff);
					if(dx > 0)
						printf("southeast %.10lf\n", fabs(dx) * sq2);
					if(dx < 0)
						printf("southwest %.10lf\n", fabs(dx) * sq2);
				} else {
					if(dx > 0)
						printf("southeast %.10lf\n", fabs(dx) * sq2);
					if(dx < 0)
						printf("southwest %.10lf\n", fabs(dx) * sq2);
					if(fabs(diff) > eps)
						printf("south %.10lf\n", diff);
				}
			} else {
				double x = x1 + dx, y = y1 + fabs(dx);
				if(x*x + y*y > r*r + eps) {
					if(fabs(diff) > eps)
						printf("north %.10lf\n", diff);
					if(dx > 0)
						printf("northeast %.10lf\n", fabs(dx) * sq2);
					if(dx < 0)
						printf("northwest %.10lf\n", fabs(dx) * sq2);
				} else {
					if(dx > 0)
						printf("northeast %.10lf\n", fabs(dx) * sq2);
					if(dx < 0)
						printf("northwest %.10lf\n", fabs(dx) * sq2);
					if(fabs(diff) > eps)
						printf("north %.10lf\n", diff);
				}
			}
		} else {
			double diff = fabs(dx) - fabs(dy);
			if(dx < 0) {
				double x = x1 - fabs(dy), y = y1 + dy;
				if(x*x + y*y > r*r + eps) {
					if(fabs(diff) > eps)
						printf("west %.10lf\n", diff);
					if(dy > 0)
						printf("northwest %.10lf\n", fabs(dy) * sq2);
					if(dy < 0)
						printf("southwest %.10lf\n", fabs(dy) * sq2);
				} else {
					if(dy > 0)
						printf("northwest %.10lf\n", fabs(dy) * sq2);
					if(dy < 0)
						printf("southwest %.10lf\n", fabs(dy) * sq2);					
					if(fabs(diff) > eps)
						printf("west %.10lf\n", diff);
				}
			} else {
				double x = x1 + fabs(dy), y = y1 + dy;
				if(x*x + y*y > r*r + eps) {
					if(fabs(diff) > eps)
						printf("east %.10lf\n", diff);
					if(dy > 0)
						printf("northeast %.10lf\n", fabs(dy) * sq2);
					if(dy < 0)
						printf("southeast %.10lf\n", fabs(dy) * sq2);
				} else {
					if(dy > 0)
						printf("northeast %.10lf\n", fabs(dy) * sq2);
					if(dy < 0)
						printf("southeast %.10lf\n", fabs(dy) * sq2);					
					if(fabs(diff) > eps)
						printf("east %.10lf\n", diff);
				}
			}
		}
	}
	return 0;
}
/*
    74.584 49.541 55.754 -43.557 -37.453
    74.584 49.541 55.754 23.560 -69.849
    74.584 -40.498 -62.632 0.540 6.183
    74.584 -40.498 -62.632 -14.154 0.389
*/
