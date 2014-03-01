#include <stdio.h>
#include <math.h>

int main() {
	int l, w, h, theta;
	while(scanf("%d %d %d %d", &l, &w, &h, &theta) == 4) {
		double b = theta/360.0 * 2 * acos(-1);
		if(l*tan(b) <= h)
			printf("%.3lf mL\n", l*w*h - w*0.5*l*l*tan(b));
		else
			printf("%.3lf mL\n", w*0.5*h*h*1/tan(b));
	}
    return 0;
}
