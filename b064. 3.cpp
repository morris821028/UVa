#include <stdio.h>
typedef struct {
    int xr, xl, yr, yl;
} seg;
int main() {
    int n, i, j;
    seg D[500];
    while(scanf("%d", &n) == 1) {
        int tmp;
        int l = 0xfffff, r = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d %d", &D[i].xl, &D[i].yl, &D[i].xr, &D[i].yr);
            if(D[i].xl > D[i].xr) {
                tmp  = D[i].xl, D[i].xl = D[i].xr, D[i].xr = tmp;
                tmp  = D[i].yl, D[i].yl = D[i].yr, D[i].yr = tmp;
            }
            if(D[i].xl < l) l = D[i].xl;
            if(D[i].xr > r) r = D[i].xr;
        }
        int prev = -1, used;
        int ans = 0;
        double x;
        for(x = l; x <= r; x += 0.5) {
            used = -1;
            double val = 0xfffff, tmp;
            for(j = 0; j < n; j++) {
                if(D[j].xl <= x && D[j].xr >= x) {
                    tmp = D[j].yl - (double)(D[j].yl-D[j].yr)*(D[j].xl-x)/(D[j].xl-D[j].xr);
                    if(tmp < val) {
                        val = tmp;
                        used = j;
                    }
                }
            }
            if(used == -1)  continue;
            if(used != prev) {
                prev = used;
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
