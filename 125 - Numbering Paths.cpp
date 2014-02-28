#include <stdio.h>
#include <string.h>
int cnt[31][31] = {};
int m, n, test = 0, x, y;
int main() {
    int i, j, k;
    while(scanf("%d", &m) == 1) {
        memset(cnt, 0, sizeof(cnt));
        n = 0;
        while(m--) {
            scanf("%d %d", &x, &y);
            cnt[x][y]++;
            if(x > n) n = x;
            if(y > n) n = y;
        }
        for(k = 0; k <= n; k++) {
            for(i = 0; i <= n; i++) {
                for(j = 0; j <= n; j++) {
                    if(cnt[i][k] != 0 && cnt[k][j] != 0) {
                        cnt[i][j] += cnt[i][k]*cnt[k][j];
                    }
                }
            }
        }
        for(k = 0; k <= n; k++) {
            if(cnt[k][k])
            for(i = 0; i <= n; i++) {
                for(j = 0; j <= n; j++) {
                    if(cnt[i][k] != 0 && cnt[k][j] != 0) {
                        cnt[i][j] = -1;
                    }
                }
            }
        }
        printf("matrix for city %d\n", test++);
        for(i = 0; i <= n; i++) {
            for(j = 0; j <= n; j++) {
                if(j)
                    putchar(' ');
                printf("%d", cnt[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
