#include <stdio.h>
#include <math.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
const double R = 6378;
const double pi = acos(-1);
int main() {
    int n, m, q;
    int i, j, k;
    double w, theta;
    double x[105], y[105], z[105];
    long long g[105][105];
    char s[105], s2[105];
    int cases = 0;
    map<string, int> gm;
    n = 0;
    while(1) {
        scanf("%s", s);
        if(!strcmp(s, "#"))
            break;
        scanf("%lf %lf", &w, &theta);
        gm[s] = n;
        w = w*pi/180.0, theta = theta*pi/180.0;
        x[n] = R*cos(w)*sin(theta);
        y[n] = R*cos(w)*cos(theta);
        z[n] = R*sin(w);
        n++;
    }
    while(true) {
        int v1, v2;
        scanf("%s %s", s, s2);
        if(!strcmp(s, "#"))
            break;
        printf("%s - %s\n", s, s2);
        if(gm.find(s) == gm.end() || gm.find(s2) == gm.end()) {
            puts("Unknown");
            continue;
        }
        v1 = gm[s];
        v2 = gm[s2];
        if(v1 == v2) {
            puts("0 km");
            continue;
        }
        double AB = sqrt(pow(x[v1]-x[v2],2)+pow(y[v1]-y[v2],2)+pow(z[v1]-z[v2],2));
        double OA = R, OB = R;
        //printf("%lf %lf %lf\n", AB, OA, OB);
        theta = acos((OA*OA+OB*OB-AB*AB)/(2*OA*OB));
        g[v1][v2] = (long long)(R*theta+0.5);
        printf("%.0lf km\n", R*theta);
    }
    return 0;
}
