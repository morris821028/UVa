#include <stdio.h>
#include <math.h>
#define oo 1000000000
int main() {
    double K, M;
    double g[105][105];
    while(scanf("%lf %lf", &K, &M) == 2) {
        double mxDis = K*M, dis, tmp;
        double x[105], y[105], r[105];
        int n, i, j, k;
        scanf("%lf %lf %lf", &x[0], &y[0], &r[0]);
        scanf("%lf %lf %lf", &x[1], &y[1], &r[1]);
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf", &x[i+2], &y[i+2], &r[i+2]);
        n += 2;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                tmp = sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2));
                if(tmp <= r[i]+r[j])
                    dis = 0;
                else
                    dis = tmp - r[i]- r[j];
                if(dis > mxDis) g[i][j] = oo;
                else g[i][j] = dis;
            }
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    if(g[i][j] > g[i][k]+g[k][j])
                        g[i][j] = g[i][k]+g[k][j];
        if(g[0][1] != oo)
            puts("Larry and Ryan will escape!");
        else
            puts("Larry and Ryan will be eaten to death.");
    }
    return 0;
}
