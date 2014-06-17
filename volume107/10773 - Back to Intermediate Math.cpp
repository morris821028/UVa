#include <stdio.h>
#include <math.h>

int main() {
    int t, test = 0;
    double d, v, u;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %lf %lf", &d, &v, &u);
        double t1 = d/u;
        double t2 = d/sqrt(u*u-v*v);
        if(v >= u || t1 == t2) {
            printf("Case %d: can't determine\n", ++test);
            continue;
        }
        printf("Case %d: %.3lf\n", ++test, t2-t1);
    }
    return 0;
}
