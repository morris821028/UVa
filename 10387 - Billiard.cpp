#include <stdio.h>
#include <math.h>

int main() {
    double a, b, s, m, n;
    const double pi = acos(-1);
    while(scanf("%lf %lf %lf %lf %lf", &a, &b, &s, &m, &n) == 5) {
        if(a == 0 && b == 0 && s == 0 && m == 0)
            break;
        double M = a*m, N = b*n;
        double A = atan(N/M)*180/pi;
        double v = sqrt(M*M + N*N)/s;
        printf("%.2lf %.2lf\n", A, v);
    }
    return 0;
}
