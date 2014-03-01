#include <stdio.h>
#include <math.h>
int main() {
    double r1, r2, r3, theta;
    double area, a, b, c, s, ans;
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %lf %lf", &r1, &r2, &r3);
        a = r1+r2, b = r2+r3, c = r3+r1;
        s = (a+b+c)/2;
        area = sqrt(s*(s-a)*(s-b)*(s-c));
        ans = area;
        theta = acos((a*a+c*c-b*b)/2/a/c);
        ans -= r1*r1*theta/2;
        theta = acos((a*a+b*b-c*c)/2/a/b);
        ans -= r2*r2*theta/2;
        theta = acos((b*b+c*c-a*a)/2/b/c);
        ans -= r3*r3*theta/2;
        printf("%lf\n", ans);
    }
    return 0;
}
