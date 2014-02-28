#include<stdio.h>
#include<math.h>
int main() {
	double n, p, k;
	while(scanf("%lf %lf", &n, &p) == 2) {
		k = exp(log(p)/n);
		printf("%.0lf\n", k);
	}
    return 0;
}
