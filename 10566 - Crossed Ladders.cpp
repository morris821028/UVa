#include <stdio.h>
#include <math.h>
#define eps 1e-5

int main() {
    double c, x, y;
    while(scanf("%lf %lf %lf", &x, &y, &c) == 3) {
        double l = 0, r = x < y ? x : y, d, tc;
        while(1) {
            d = (l+r)/2;
            tc = sqrt(y*y-d*d)*sqrt(x*x-d*d)/(sqrt(y*y-d*d)+sqrt(x*x-d*d));
            if(fabs(tc-c) <= eps)
                break;
            if(tc > c)
                l = d;
            else
                r = d;
        }
        printf("%.3lf\n", d);
    }
    return 0;
}
