#include <stdio.h>
#include <math.h>

int main() {
    double s, a;
    const double pi = acos(-1);
    char cmd[20];
    while(scanf("%lf %lf", &s, &a) == 2) {
        scanf("%s", cmd);
        if(cmd[0] == 'm')
            a /= 60;
        if(a > 180)
            a = 360-a;
        s += 6440;
        printf("%.6lf %.6lf\n", s*a/180*pi, 2*sqrt(s*s-pow(s*cos(a/360*pi), 2)));
    }
    return 0;
}
