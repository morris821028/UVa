#include <stdio.h>
#include <math.h>
#define eps 1e-6
int main() {
    int t, cases = 0, n, m, i;
    char kind[150][50];
    double px[150], py[150], len[150], x, y;
    int r[150], g[150], b[150];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s %lf %lf %lf %d %d %d", kind[i], px+i, py+i
                  , len+i, r+i, g+i, b+i);
        printf("Case %d:\n", ++cases);
        while(m--) {
            scanf("%lf %lf", &x, &y);
            int ar = 0, ag = 0, ab = 0;
            int cnt = 0;
            for(i = 0; i < n; i++) {
                if(kind[i][0] == 'C') {
                    if(pow(px[i]-x, 2)+pow(py[i]-y, 2) <= len[i]*len[i]) {
                        if(fabs(pow(px[i]-x, 2)+pow(py[i]-y, 2) - len[i]*len[i]) < eps)
                            {ar = ag = ab = 0, cnt = 1;break;} // borderline
                        else
                            ar += r[i], ag += g[i], ab += b[i];
                        cnt++;
                    }
                } else {
                    if(px[i] <= x && x <= px[i]+len[i] && py[i] <= y && y <= py[i]+len[i]) {
                        if(fabs(x-px[i]) < eps || fabs(x-px[i]-len[i]) < eps ||
                           fabs(y-py[i]) < eps || fabs(y-py[i]-len[i]) < eps)
                           {ar = ag = ab = 0, cnt = 1;break;}
                        else
                            ar += r[i], ag += g[i], ab += b[i];
                        cnt++;
                    }
                }
            }
            if(cnt == 0)
                ar = ag = ab = 255, cnt++;
            if(ar%cnt*2 >= cnt)
                ar = ar/cnt+1;
            else
                ar /= cnt;
            if(ag%cnt*2 >= cnt)
                ag = ag/cnt+1;
            else
                ag /= cnt;
            if(ab%cnt*2 >= cnt)
                ab = ab/cnt+1;
            else
                ab /= cnt;
            printf("(%d, %d, %d)\n", ar, ag, ab);
        }
        if(t)   puts("");
    }
    return 0;
}
