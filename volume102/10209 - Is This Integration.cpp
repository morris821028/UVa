#include <stdio.h>
#include <math.h>

int main() {
    double PI = acos(-1), a;
    while(scanf("%lf", &a) == 1) {
        double x, y, z;
        z = a*a - a*a*PI/4;
        z -= a*a*PI/4 - a*a*PI/6 - ( a*a*PI/6 - a*a*sqrt(3.0)/4 );
        y = a*a - a*a*PI/4 - 2*z;
        x = a*a - 4*y - 4*z;
        printf("%.3lf %.3lf %.3lf\n", x, 4*y ,4*z);
    }
    return 0;
}
