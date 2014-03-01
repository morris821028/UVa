#include <stdio.h>

int main() {
    long long a, b, c, d;
    double eps;
    while(scanf("%lld %lld", &a, &b) == 2) {
        scanf("%lf", &eps);
        long double t1 = (long double)a/b, t2;
        for(d = 1; ; d++) {
            c = (long long)(t1*d);
            while(a*d >= b*c)
                c++;
            t2 = (long double)c/d;
            if(t2-t1 <= eps) {
                printf("%lld %lld\n", c, d);
                break;
            }
        }
    }
    return 0;
}
/*
89 144 0.00000001
*/

