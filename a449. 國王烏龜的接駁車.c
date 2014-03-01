#include <stdio.h>

int main() {
    int n, k, m;
    while(scanf("%d %d %d", &n, &k, &m) == 3) {
        int i, j, wi;
        int dpc[2005] = {}, dpw[2005] = {};
        for(i = 1; i <= n; i++)
            dpc[i] = n+1, dpw[i] = 0xffffff;
        dpc[0] = 1, dpw[0] = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &wi);
            if(wi > m)  continue;
            for(j = i; j >= 0; j--) {
                if(dpw[j] + wi > m) {
                    if(dpc[j]+1 < dpc[j+1] || (dpc[j]+1 == dpc[j+1] && wi < dpw[j+1])) {
                        if(dpc[j]+1 > k)    continue;
                        dpc[j+1] = dpc[j]+1, dpw[j+1] = wi;
                    }
                } else {
                    if(dpc[j] < dpc[j+1] || (dpc[j] == dpc[j+1] && dpw[j]+wi < dpw[j+1]))
                        dpc[j+1] = dpc[j], dpw[j+1] = dpw[j]+wi;
                }
            }
        }
        i = n;
        while(dpc[i] == n+1)    i--;
        printf("%d\n", i);
    }
    return 0;
}
