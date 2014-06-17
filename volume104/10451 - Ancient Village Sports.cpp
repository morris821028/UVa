#include <stdio.h>
#include <math.h>

int main() {
    int cases = 0;
    double n, A;
    const double pi = acos(-1);
    while(scanf("%lf %lf", &n, &A) == 2) {
        if(n < 3)  break;
        double theta = pi-2*pi/n;
        double R = sqrt(2*A/(n*sin(pi-theta)));
        double r = R*sin(theta/2);
        printf("Case %d: %.5lf %.5lf\n", ++cases, R*R*pi-A, A-r*r*pi);
    }
    return 0;
}
