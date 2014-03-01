#include <stdio.h>
#include <math.h>

int main() {
    double r, r1, r2, r3;
    int cases = 0;
    while(scanf("%lf %lf %lf %lf", &r, &r1, &r2, &r3) == 4) {
        if(r < 0)   break;
        double p1, p2, p3, a, b, c;
        p1 = r/(r-r1)*sqrt(pow(r+r1, 2)-pow(r-r1, 2));
        p2 = r/(r-r2)*sqrt(pow(r+r2, 2)-pow(r-r2, 2));
        p3 = r/(r-r3)*sqrt(pow(r+r3, 2)-pow(r-r3, 2));
        a = p1+p2, b = p2+p3, c = p3+p1;
        printf("Case %d: %.2lf", ++cases, (a+b+c)*r/2);
        puts("");
    }
    return 0;
}
