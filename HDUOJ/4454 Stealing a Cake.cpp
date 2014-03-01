#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int main() {
    double x, y, cx, cy, cr;
    double x1, x2, y1, y2, xx, yy;
    double pi = acos(-1);
    while(scanf("%lf %lf", &x ,&y) == 2) {
        if(x == 0 && y == 0)
            break;
        scanf("%lf %lf %lf", &cx, &cy, &cr);
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        double theta, ans = 0xffffffffLL;
        double tmp, tmp2;
        for(theta = 0; theta <= 360; theta+=0.01) {
            xx = cx+cr*cos(theta/180*pi);
            yy = cy+cr*sin(theta/180*pi);
            tmp = sqrt(pow(xx-x, 2)+pow(yy-y, 2));
            tmp2 = 0xffffffffLL;
            tmp2 = min(tmp2, sqrt(pow(xx-x1,2)+pow(yy-y1,2)));
            tmp2 = min(tmp2, sqrt(pow(xx-x1,2)+pow(yy-y2,2)));
            tmp2 = min(tmp2, sqrt(pow(xx-x2,2)+pow(yy-y1,2)));
            tmp2 = min(tmp2, sqrt(pow(xx-x2,2)+pow(yy-y2,2)));
            if(xx >= x1 && xx <= x2) {
                tmp2 = min(tmp2, fabs(yy-y1));
                tmp2 = min(tmp2, fabs(yy-y2));
            }
            if(yy >= y1 && yy <= y2) {
                tmp2 = min(tmp2, fabs(xx-x1));
                tmp2 = min(tmp2, fabs(xx-x2));
            }
            tmp += tmp2;
            if(tmp <= ans)
                ans = tmp;
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
