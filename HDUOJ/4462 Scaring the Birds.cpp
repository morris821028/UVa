#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, k, h1, h2;
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d", &k);
        int x[20], y[20], r[20], i, j;
        for(i = 0; i < k; i++)
            scanf("%d %d", &x[i], &y[i]);
        for(i = 0; i < k; i++)
            scanf("%d", &r[i]);
        int can = 0, ans = 0xffff;
        for(i = (1<<k)-1; i >= 0; i--) {
            int cnt = 0, cover = 0;
            for(h1 = 1; h1 <= n; h1++)
                for(h2 = 1; h2 <= n; h2++) {
                    for(j = 0; j < k; j++) {
                        if(h1 == x[j] && h2 == y[j]) {
                            cover++;
                            break;
                        }
                        if((i>>j)&1) {
                            if(abs(x[j]-h1)+abs(y[j]-h2) <= r[j]) {
                                cover++;
                                break;
                            }
                        }
                    }
                }
            for(j = 0; j < k; j++)
                if((i>>j)&1)
                    cnt++;
            if(cover == n*n) {
                if(cnt < ans)
                    ans = cnt;
                can = 1;
            }
        }
        if(can == 0)
            puts("-1");
        else
            printf("%d\n", ans);
    }
    return 0;
}
