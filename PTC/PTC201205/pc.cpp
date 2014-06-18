#include<stdio.h>
#include<string.h>
int map[2002][2002], mt[2002];
int dp[2002][2002];
int n, a, b;
main() {
    int test;
    scanf("%d", &test);
    while(test--) {
        scanf("%d", &n);
        memset(mt, 0, sizeof(mt));
        memset(dp, 0, sizeof(dp));
        int i, j, k, m, x;
        for(i = 1; i <= n; i++) {
            scanf("%d", &m);
            mt[i] = m;
            for(j = 0; j < m; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        for(i = n+1; i <= 2*n; i++) {
            scanf("%d", &m);
            mt[i] = m;
            for(j = 0; j < m; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        int total[2002] = {};
        for(i = n+1; i <= 2*n; i++) {
            int used[2002] = {};
            for(j = 0; j < mt[i]; j++) {
                for(k = j+1; k < mt[i]; k++) {
                    //printf("m = %d m' = %d\n", map[i][k], map[i][j]);
                    dp[map[i][k]][map[i][j]]++;
                }
                used[map[i][j]] = 1;
            }
            for(j = 1; j <= n; j++) {
                if(used[j] == 0) {
                    total[j] += mt[i];
                }
            }
        }
        int ans = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                if(dp[i][j]+total[i] > ans)
                    ans = dp[i][j]+total[i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
