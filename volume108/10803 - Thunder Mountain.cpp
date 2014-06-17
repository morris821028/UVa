#include <stdio.h>
#include <math.h>
#define oo 1000000
double g[105][105];
int main() {
    int cases = 0, n;
    scanf("%*d");
    while(scanf("%d", &n) == 1) {
        double x[105], y[105];
        int i, j, k;
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &x[i], &y[i]);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                g[i][j] = oo;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                double tmp = sqrt(pow(x[i]-x[j], 2)+pow(y[i]-y[j], 2));
                if(tmp <= 10)
                    g[i][j] = tmp;
            }
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    if(g[i][j] > g[i][k] + g[k][j])
                        g[i][j] = g[i][k] + g[k][j];
        double res = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(g[i][j] > res)
                    res = g[i][j];
        printf("Case #%d:\n", ++cases);
        if(res == oo)
            puts("Send Kurdy");
        else
            printf("%.4lf\n", res);
        puts("");
    }
    return 0;
}
