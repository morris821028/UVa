#include <stdio.h>
#include <math.h>
#define eps 1e-8
int main() {
    double l, w;
    while(scanf("%lf %lf", &l, &w) == 2) {
        double mx;
        mx = (l+w - sqrt(w*w-w*l+l*l))/6.0;
        if(l > w)   l = w;
        printf("%.3lf %.3lf %.3lf\n", mx+eps, 0.0, l/2.0+eps);
    }
    return 0;
}
