#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int sk1[100], sk2[100];
        int idx = -1, i;
        int tot = 0, p = 0, v, w;
        int vv[100], ww[100];
        for(i = n-1; i >= 0; i--)
            scanf("%d %d", &vv[i], &ww[i]);
        for(i = 0; i < n; i++) {
            v = vv[i], w = ww[i];
            if(tot+w <= 20) {
                ++idx;
                sk1[idx] = v, sk2[idx] = w;
                tot += w, p += v;
            } else {
                if((double)sk1[idx]/sk2[idx] > (double)v/w) continue;
                if((double)sk1[idx]/sk2[idx] < (double)v/w) {
                    tot -= sk2[idx], p -= sk1[idx];
                    sk1[idx] = v, sk2[idx] = w;
                    tot += w, p += v;
                }
            }
        }
        printf("%d %d\n", p, tot);
    }
    return 0;
}
