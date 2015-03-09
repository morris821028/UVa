#include <stdio.h>
#include <math.h>
const double pi = acos(-1);
int main() {
    int t, n, i, j, k;
    double xi[105], yi[105], ri[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf", &xi[i], &yi[i], &ri[i]);
        double ans = 0;
        double theta, x, y;
        int chbuf[105], m;
        for(i = 0; i < n; i++) {
            m = 0;
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                if(pow(xi[i]-xi[j], 2)+pow(yi[i]-yi[j], 2) < pow(ri[i]+ri[j], 2))
                    chbuf[m++] = j;
            }
#define pp 10000
            double ll = 0;
            int flag = 1, cnt = 0;
            for(j = 0; j < pp; j++) {
                theta = 360.0*j*pi/180/pp;
                x = ri[i]*cos(theta) + xi[i];
                y = ri[i]*sin(theta) + yi[i];
                for(k = 0; k < m; k++) {
                    if(pow(x-xi[chbuf[k]], 2)+pow(y-yi[chbuf[k]], 2) < ri[chbuf[k]]*ri[chbuf[k]])
                        break;
                }
                if(k == m)
                    cnt++;
            }
            ans += 2*pi*ri[i]*cnt/pp;
        }
        double a = log10(ans), b;
        b = floor(a);
        a = a-b;
        printf("%.2lf %d\n", pow(10, a), (int)b);
    }
    return 0;
}
