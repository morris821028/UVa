#include <stdio.h>
#include <math.h>
int main() {
	int n, m;
	while(scanf("%d:%d", &n, &m) == 2) {
		if(n == 0 && m == 0)	break;
		double H = n*30 + m*0.5, M = m*6;
		double A = fabs(H-M);
		if(A > 180)	A = 360 - A;
		printf("%.3lf\n", A);
	}
    return 0;
}
