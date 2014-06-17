#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int m, n, rank, i, j, cnt[32] = {};
        scanf("%d %d", &m, &n);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%d", &rank);
                if(rank == 1)
                    cnt[j]++;
            }
        }
        int ans = 1;
        for(i = 0; i < m; i++) {
            if(cnt[i])
                ans *= cnt[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
