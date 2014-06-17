#include <stdio.h>
#include <math.h>

int main() {
    double R, N;
    double pi = acos(-1);
    while(scanf("%lf %lf", &R, &N) == 2) {
        double theta = (pi - 2*pi/N)/2;
        double x, y, z;
        if(N <= 2) {
            x = R/N;
        } else {
            x = R/(1+1/cos(theta));
        }
        if(N <= 2) {
            y = 0;
        } else {
            y = (R-x)*(R-x)*sin(2*pi/N)*N/2;
            y -= x*x*pi*(theta*2*N/pi/2);
        }
        z = R*R*pi-y-x*x*pi*N;
        printf("%.10lf %.10lf %.10lf\n", x, y, z);
    }
    return 0;
}
