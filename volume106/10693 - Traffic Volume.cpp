#include <stdio.h>
#include <math.h>

int main() {
    double L, f;
    while(scanf("%lf %lf", &L, &f) == 2) {
        double v = sqrt(2*L*f);
        double fun = 3600*v/(L+v*v/2/f);
        printf("%.8lf %.8lf\n", v, fun);
    }
    return 0;
}
