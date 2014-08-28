#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

#define eps 1e-8
int main() {
    int testcase;
    double R, P;
    const double pi = acos(-1);
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lf %lf", &R, &P);
        double l = 0, r = pi, mid, ret = 0;
        double A = R * R * pi;
        while (fabs(l - r) > eps) {
            mid = (l + r)/2;
            ret = hypot(R * cos(mid) - R, R * sin(mid));
            double theta = (pi - mid)/2;
            double area = (ret * ret * theta/2 + (R * R * mid/2 - R * R * sin(mid)/2))*2;
            if (area < A * P)
                l = mid;
            else
                r = mid;
        }
        printf("R = %.0lf, P = %.2lf, Rope = %.2lf\n", R, P, ret);
        if(testcase)
            puts("");
    }
    return 0;
}
/*

*/