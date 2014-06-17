#include <stdio.h>
#include <math.h>
const double R = 6371.01;
const double pi = acos(-1);
double angle_3d(double lng1, double lat1, double lng2, double lat2) {
    return acos(cos(lat1)*cos(lat2)*cos(lng1 - lng2) + sin(lat1)*sin(lat2));
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        double a, b, c;
        double W[2], THETA[2];
        char dir[10];
        scanf("%lf %lf %lf %s", &a, &b, &c, &dir);
        W[0] = a + b/60 + c/3600;
        if(dir[0] == 'S')   W[0] = -W[0];
        scanf("%lf %lf %lf %s", &a, &b, &c, &dir);
        THETA[0] = a + b/60 + c/3600;
        if(dir[0] == 'W')   THETA[0] = -THETA[0];
        scanf("%lf %lf %lf %s", &a, &b, &c, &dir);
        W[1] = a + b/60 + c/3600;
        if(dir[0] == 'S')   W[1] = -W[1];
        scanf("%lf %lf %lf %s", &a, &b, &c, &dir);
        THETA[1] = a + b/60 + c/3600;
        if(dir[0] == 'W')   THETA[1] = -THETA[1];
        W[0] = W[0]*pi/180.0, THETA[0] = THETA[0]*pi/180.0;
        W[1] = W[1]*pi/180.0, THETA[1] = THETA[1]*pi/180.0;
        printf("%.2lf\n", R*angle_3d(THETA[0], W[0], THETA[1], W[1]));
    }
    return 0;
}
