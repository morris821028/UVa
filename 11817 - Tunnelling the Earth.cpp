#include <stdio.h>
#include <math.h>
const double R = 6371009;
const double pi = acos(-1);
double angle_3d(double lng1, double lat1, double lng2, double lat2) {
    return acos(cos(lat1)*cos(lat2)*cos(lng1 - lng2) + sin(lat1)*sin(lat2));
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        double W[2], THETA[2];
        scanf("%lf %lf %lf %lf", &W[0], &THETA[0], &W[1], &THETA[1]);
        W[0] = W[0]*pi/180.0, THETA[0] = THETA[0]*pi/180.0;
        W[1] = W[1]*pi/180.0, THETA[1] = THETA[1]*pi/180.0;
        double theta = angle_3d(THETA[0], W[0], THETA[1], W[1]);
        double straight = R*sqrt(1*1+1*1-2*1*1*cos(theta));
        printf("%.0lf\n", R*theta-straight);
    }
    return 0;
}
