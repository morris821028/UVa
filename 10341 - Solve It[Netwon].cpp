#include <stdio.h>
#include <math.h>
#define eps 1e-9

int p, q, r, s, t, u;
double calc1(double xn) {
    return p*exp(-xn) + q*sin(xn) + r*cos(xn) + s*tan(xn) + t*xn*xn + u;
}
double calc2(double xn) {
    return -p*exp(-xn) + q*cos(xn) - r*sin(xn) + s/cos(xn)/cos(xn) + t*2*xn;
}
int main() {
    while(scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) == 6) {
        if(calc1(1)*calc1(0) > 0) {
            puts("No solution");
            continue;
        }
        if(fabs(calc1(0)) < eps) {
            puts("0.0000");
            continue;
        }
        if(fabs(calc1(1)) < eps) {
            puts("1.0000");
            continue;
        }
        double xn = 1, fx;
        while(1) {
            fx = calc1(xn);
            if(fabs(fx) < eps) {
                break;
            }
            xn = xn - fx/calc2(xn);
        }
        printf("%.4lf\n", xn);
    }
    return 0;
}
