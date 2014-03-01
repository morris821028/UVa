#include <stdio.h>
#include <math.h>

int main() {
    long long a, b, c;
    while(scanf("%lld %lld %lld", &a, &b, &c) == 3) {
        double roses, violets, sunflowers;
        double r, R, s = (a+b+c)/2.0;
        violets = sqrt(s*(s-a)*(s-b)*(s-c));
        r = violets*2/(double)(a+b+c);
        roses = r*r*acos(-1);
        R = a*b*c / 4.0 / violets;
        sunflowers = R*R * acos(-1) - violets;
        violets -= roses;
        printf("%.4lf %.4lf %.4lf\n", sunflowers, violets, roses);

    }
    return 0;
}
