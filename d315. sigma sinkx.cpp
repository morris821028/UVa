#include <stdio.h>
#include <math.h>
int main() {
    double n, x;
    const double pi = acos(-1);
    int cases = 0;
    while(scanf("%lf %lf", &n, &x) == 2) {
        double y = x*pi/180;
        printf("%.4lf\n", sin((n*y+y)/2)*sin(n*y/2)/sin(y/2));
        //printf("%.4lf\n", (cos(y/2)-cos((n+0.5)*y))/(2*sin(y/2)));
        //printf("%.4lf\n", (sin(n*y)+sin(y)-sin((n+1)*y))/(2-2*cos(y)));
    }
    return 0;
}
/*
1 60
3 60
2147483647 30
338 1778
0 0
*/
