#include <stdio.h>
#include <math.h>
#define eps 1e-2
int main() {
    int t, i;
    scanf("%d", &t);
    double A, B, pi = acos(-1);
    while(t--) {
        scanf("%lf %lf", &A, &B);
        if(A == 0 && B == 0) {
            puts("0.00 0.00");
            continue;
        }
        double tmp1, tmp2;
        double F = sqrt(A*A+B*B);
        tmp1 = atan(A/B);
        for(; tmp1 <= 2*pi; tmp1+=pi/2) {
            if(fabs(A*sin(tmp1)+B*cos(tmp1)-F) < eps && tmp1 >= 0)
                break;
        }
        printf("%.2lf %.2lf\n", tmp1, F);
    }
    return 0;
}
