#include <stdio.h>
#include <math.h>
int main() {
    int n, i, j;
    double CF[20];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i <= n; i++)
            scanf("%lf", &CF[i]);
        double l = -1, r = 10000, mid;
        int cnt = 0;
        while(l <= r && cnt < 100) {
            mid = (l+r)/2;
            cnt++;
            double NPV = 0;
            for(i = 0; i <= n; i++)
                NPV += CF[i]/pow(1+mid, i);
            if(NPV > 0) l = mid;
            else        r = mid;
        }
        printf("%.2lf\n", mid);
    }
    return 0;
}
