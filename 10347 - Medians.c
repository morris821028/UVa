#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    while(scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        if(a+b <= c || b+c <= a || c+a <= b) {
            puts("-1.000");
            continue;
        }
        a = a*(2/3.0);
        b = b*(2/3.0);
        c = c*(2/3.0);
        double s = (a+b+c)/2.0;
        printf("%.3lf\n", 3*sqrt(s*(s-a)*(s-b)*(s-c)));
    }
    return 0;
}
