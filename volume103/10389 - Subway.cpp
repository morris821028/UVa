#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
struct Pt{
    double x, y;
};
double dist(Pt a, Pt b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main() {
    int t, i, j, k;
    scanf("%d", &t);
    while(t--) {
        Pt p[250];
        double g[250][250] = {};
        scanf("%lf %lf", &p[0].x, &p[0].y);
        scanf("%lf %lf", &p[1].x, &p[1].y);
        cin.ignore(100, '\n');
        string line;
        int n = 2;
        while(getline(cin, line)) {
            if(line == "")  break;
            stringstream sin;
            sin << line;
            sin >> p[n].x >> p[n].y, n++;
            while(sin >> p[n].x >> p[n].y) {
                if(p[n].x < 0)    break;
                g[n-1][n] = dist(p[n], p[n-1]);
                g[n][n-1] = g[n-1][n];
                n++;
            }
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(g[i][j] == 0) {
                    g[i][j] = dist(p[i], p[j])*4;
                }
            }
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
        printf("%d\n", (int)(g[0][1]*6/4000+0.5));
        if(t)
            puts("");
    }
    return 0;
}
