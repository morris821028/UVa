#include <stdio.h>
#include <math.h>
int main() {
    int cases = 0;
    double a, b;
    const double pi = acos(-1);
    while(scanf("%lf : %lf", &a, &b) == 2) {
        printf("Case %d: ", ++cases);
        double l = 0, r = 1000, R;
        int cnt = 0;
        double theta = atan2(a, b), length, width, arc;
        while(l <= r && cnt < 50) {
            R = (l+r)/2;
            length = R*sin(theta)*2;
            width = R*cos(theta)*2;
            arc = R*(pi - 2*theta)*2;
            if(arc + 2*length > 400)
                r = R;
            else
                l = R;
            cnt++;
        }
        printf("%.10lf %.10lf\n", length, width);
    }
    return 0;
}
