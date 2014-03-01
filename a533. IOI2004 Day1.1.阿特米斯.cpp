#include <stdio.h>
#include <stdlib.h>
typedef struct {
    unsigned short x, y;
} Pt;
int cmp(const void *i, const void *j) {
    static Pt *a, *b;
    a = (Pt *)i, b = (Pt *)j;
    return a->x - b->x;
}
int main() {
    int n, t, i, j;
    while(scanf("%d %d", &n, &t) == 2) {
        Pt D[n];
        int L = 0;
        for(i = 0; i < n; i++) {
            scanf("%hu %hu", &D[i].x, &D[i].y);
            D[i].x++, D[i].y++;
            if(D[i].y > L) L = D[i].y;
        }
        qsort(D, n, sizeof(Pt), cmp);
        int ans = 0xfffffff;
        for(i = 0; i < n; i++) {
            short upC[64005] = {}, doC[64005];
            int uCnt = 0, dCnt = 0, idx, sum;
            for(j = i; j < n; j++) {
                if(D[j].y >= D[i].y) {
                    uCnt++;
                    idx = D[j].y;
                    while(idx <= L) {
                        upC[idx]++;
                        idx += idx&(-idx);
                    }
                    if(uCnt >= t) {
                        sum = 0, idx = D[j].y;
                        while(idx) {
                            sum += upC[idx];
                            idx -= idx&(-idx);
                        }
                        if(sum >= t && sum < ans)
                            ans = sum;
                    }
                } else {
                    dCnt++;
                    idx = D[j].y;
                    while(idx <= D[i].y) {
                        doC[idx]++;
                        idx += idx&(-idx);
                    }
                    if(dCnt >= t) {
                        sum = 0, idx = D[j].y;
                        while(idx) {
                            sum += doC[idx];
                            idx -= idx&(-idx);
                        }
                        sum = dCnt - sum;
                        if(sum >= t && sum < ans)
                            ans = sum;
                    }
                }
            }
            if(ans == t)    break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
