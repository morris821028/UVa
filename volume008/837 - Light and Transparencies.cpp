#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
    int t, nl;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &nl);
        double l[100], r[100], n[100], y;
        double x[200];
        int i, j, idx = 0;
        for(i = 0; i < nl; i++) {
            scanf("%lf %lf %lf %lf %lf", l+i, &y, r+i, &y, n+i);
            x[idx++] = l[i], x[idx++] = r[i];
        }
        sort(x, x+idx);
        int didx = 0;
        double diff[200] = {x[0]};
        for(i = 1; i < idx; i++) {
            if(x[i] != diff[didx]) {
                diff[++didx] = x[i];
            }
        }
        printf("%d\n", didx+2);
        printf("-inf %.3lf 1.000\n", diff[0]);
        for(i = 0; i < didx; i++) {
            double m = (diff[i]+diff[i+1])/2, nn = 1;
            for(j = 0; j < nl; j++) {
                if((l[j] <= m && m <= r[j]) ||
                    (l[j] >= m && m >= r[j]))
                        nn *= n[j];
            }
            printf("%.3lf %.3lf %.3lf\n", diff[i], diff[i+1], nn);
        }
        printf("%.3lf +inf 1.000\n", diff[didx]);
        if(t)
            puts("");
    }
    return 0;
}
