#include <stdio.h>
#include <math.h>

int main() {
    double f;
    while(scanf("%lf", &f) == 1 && f) {
        double a = floor(pow(f, 1/3.0)+1e-6);
        double dx = (f-a*a*a)/3.0/a/a;
        printf("%.4lf\n", a+dx);
    }
    return 0;
}
