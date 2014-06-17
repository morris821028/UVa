#include <stdio.h>
#include <math.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
const double R = 6378;
const double pi = acos(-1);
#define eps 1e-6
int main() {
    int n;
    int i, j, k;
    double w, theta;
    double x[1005], y[1005], z[1005];
    double W[1005], THETA[1005];
    int cases = 0;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &W[i], &THETA[i]);
            w = W[i]*pi/180.0, theta = THETA[i]*pi/180.0;
            x[i] = R*cos(w)*sin(theta);
            y[i] = R*cos(w)*cos(theta);
            z[i] = R*sin(w);
        }
        double mx, mn = 1e+30;
        double rx = W[0], ry = THETA[0];
        for(i = 0; i < n; i++) {
            mx = 0;
            for(j = 0; j < n; j++) {
                if(i == j)
                    continue;
                double AB = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
                double OA = R, OB = R;
                theta = acos((OA*OA+OB*OB-AB*AB)/(2*OA*OB));
                mx = max(mx, R*theta);
                if(mx > mn+eps) break;
            }
            if(mn >= mx-eps) {
                mn = mx;
                rx = W[i];
                ry = THETA[i];
            }
        }
        printf("%.2lf %.2lf\n", rx, ry);
    }
    return 0;
}
