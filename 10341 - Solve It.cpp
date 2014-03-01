#include <stdio.h>
#include <math.h>
#define eps 1e-15

int p, q, r, s, t, u;
double calc(double xn) {
    return p*exp(-xn) + q*sin(xn) + r*cos(xn) + s*tan(xn) + t*xn*xn + u;
}
double bsearch() {
    double mx, a, b, m;
    int test = 50;
    a = 0, b = 1;
    while(test--) {
        m = (a+b)/2;
        mx = calc(m);
        if(fabs(mx) < eps)
            return m;
        if(mx > 0)  a = m;
        else        b = m;
    }
    return -1;
}
int main() {
    int cases = 0;
    while(scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) == 6) {
        if(!p && !q && !r && !s && !t && !u) {
            puts("0.0000");
            continue;
        }
        double flag = bsearch();
        if(flag == -1) {
            puts("No solution");
        } else
            printf("%.4lf\n", flag);
    }
    return 0;
}
