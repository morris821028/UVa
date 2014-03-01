#include <stdio.h>
#include <stdlib.h>
int cmp(const void *i, const void *j) {
    return *(int *)i - *(int *)j;
}
int main() {
    int L, S, T, M;
    int x[105], i, j;
    while(scanf("%d", &L) == 1) {
        scanf("%d %d %d", &S, &T, &M);
        x[0] = 0, x[M+1] = L;
        for(i = 1; i <= M; i++)
            scanf("%d", &x[i]);
        M += 2;
        qsort(x, M, sizeof(int), cmp);
        if(S == T) {
            int ans = 0;
            for(i = 1; i <= M; i++)
                if(x[i]%S == 0)
                    ans++;
            printf("%d\n", ans);
            continue;
        }

        for(i = 1; i < M; i++) {
            if(x[i] - x[i-1] > 100) {
                int del = x[i]-x[i-1]-100;
                for(j = i; j < M; j++)
                    x[j] -= del;
            }
        }
        int dp[20050] = {}, mark[20050] = {};
        for(i = 1; i <= M-2; i++)
            mark[x[i]] = 1;
        int ll = x[M-1];
        for(i = 1; i <= ll; i++) {
            int mx = 0xffff;
            for(j = S; j <= T; j++) {
                if(i-j >= 0 && dp[i-j] < mx)
                    mx = dp[i-j];
            }
            dp[i] = mx + mark[i];
        }
        int ans = 0xffff;
        for(i = ll; i >= 0; i--) {
            if(i >= ll-T && ans > dp[i])
                ans = dp[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
