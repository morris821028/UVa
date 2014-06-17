#include <stdio.h>
#include <math.h>
#define pi acos(-1)
#define Sin(x) sin(x*pi/180.0)
int main() {
    double f;
    while(scanf("%lf", &f) == 1) {
        printf("%.10lf\n", Sin(108)/Sin(63)*f);
    }
    return 0;
}
