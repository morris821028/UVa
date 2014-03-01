#include <stdio.h>
#include <math.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
const double R = 6378;
const double pi = acos(-1);
int main() {
    int n, m, q;
    int i, j, k;
    double w, theta;
    double x[105], y[105], z[105];
   long long g[105][105];
    char s[105];
    int cases = 0;
    while(scanf("%d %d %d", &n, &m, &q) == 3) {
        if(n+m+q == 0)
            break;
        map<string, int> gm;
        for(i = 0; i < n; i++) {
            scanf("%s %lf %lf", s, &w, &theta);
            gm[s] = i;
            w = w*pi/180.0, theta = theta*pi/180.0;
            x[i] = R*cos(w)*sin(theta);
            y[i] = R*cos(w)*cos(theta);
            z[i] = R*sin(w);
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                g[i][j] = 0xffffffffLL;
            }
            g[i][i] = 0;
        }
        while(m--) {
            int v1, v2;
            scanf("%s", s);
            v1 = gm[s];
            scanf("%s", s);
            v2 = gm[s];
            if(v1 == v2)    continue;
            double AB = sqrt(pow(x[v1]-x[v2],2)+pow(y[v1]-y[v2],2)+pow(z[v1]-z[v2],2));
            double OA = R, OB = R;
            //printf("%lf %lf %lf\n", AB, OA, OB);
            theta = acos((OA*OA+OB*OB-AB*AB)/(2*OA*OB));
            g[v1][v2] = (long long)(R*theta+0.5);
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
        if(cases)   puts("");
        printf("Case #%d\n", ++cases);
        while(q--) {
            int v1, v2;
            scanf("%s", s);
            v1 = gm[s];
            scanf("%s", s);
            v2 = gm[s];
            if(g[v1][v2] == 0xffffffffLL)
                puts("no route exists");
            else
                printf("%lld km\n", g[v1][v2]);
        }
    }
    return 0;
}
