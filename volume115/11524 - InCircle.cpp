#include <stdio.h>
#include <math.h>

int main() {
    scanf("%*d");
    double r, n1, m1, n2, m2, n3, m3;
    while(scanf("%lf", &r) == 1) {
        scanf("%lf %lf %lf %lf %lf %lf", &m1, &n1, &m2, &n2, &m3, &n3);
        double a, b, c, ta, tb, tc;
        a = n1*n3;
        b = m1*n3;
        c = m3*m1;
        ta = a+b;
        tb = b+c;
        tc = a+c;
        double area, s, x;
        s = (ta+tb+tc)/2;
        area = sqrt(s*(s-ta)*(s-tb)*(s-tc));
        x = r*(ta+tb+tc)/2/area;
        printf("%.4lf\n", area*x*x);
    }
    return 0;
}
