#include <stdio.h>
#include <math.h>
#define eps 1e-8
int main() {
    int t, n, m, cases = 0, i, j;
    double x[105], y[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%lf %lf", x+i, y+i);
        printf("Road #%d:\n", ++cases);
        double path = 0, sum = 0, pre = 0;
        for(i = 1; i < n; i++)
            path += sqrt(pow(x[i]-x[i-1], 2)+pow(y[i]-y[i-1],2));
        path /= m-1;
        printf("%.2lf %.2lf\n", x[0], y[0]);
        for(i = 1; i < n; i++) {
            double len = sqrt(pow(x[i]-x[i-1], 2)+pow(y[i]-y[i-1],2));
            double sx = x[i-1], sy = y[i-1], ex = x[i], ey = y[i];
            pre = sum;
            if(sum+len >= path-eps) {
                double d = path - sum;
                sum = 0;
                sx = sx + d/len*(ex-sx);
                sy = sy + d/len*(ey-sy);
                printf("%.2lf %.2lf\n", sx, sy);
                len -= d;
                d = path;
                while(len >= path-eps) {
                    sx = sx + d/len*(ex-sx);
                    sy = sy + d/len*(ey-sy);
                    printf("%.2lf %.2lf\n", sx, sy);
                    len -= path;
                }
            }
            sum += len;
        }
        puts("");
    }
    return 0;
}
