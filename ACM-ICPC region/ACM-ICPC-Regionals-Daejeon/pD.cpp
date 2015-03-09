#include <stdio.h>
int n, k, ans;
int r[10001][5], reduce[5];
void dfs(int idx, int tk) {
    int i, j;
    if(idx == 5) {
        int mm[5] = {}, tmp = 0;
        for(i = 0; i < n; i++) {
            int tm[5] = {};
            for(j = 0; j < 5; j++)
                tm[reduce[j]] += r[i][j];
            for(j = 0; j < 5; j++)
                mm[j] = mm[j] > tm[j] ? mm[j] : tm[j];
        }
        for(i = 0; i < 5; i++)
            tmp += mm[i];
        if(ans < tmp)   ans = tmp;
        return;
    }
    for(i = 0; i < tk; i++) {
        reduce[idx] = i;
        dfs(idx+1, tk);
    }
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        for(i = 0; i < n; i++) {
            for(j = 0; j < 5; j++)
                scanf("%d", &r[i][j]);
        }
        if(k >= 5) {
            int ans = 0;
            for(i = 0; i < 5; i++) {
                int tmp = 0;
                for(j = 0; j < n; j++) {
                    if(r[j][i] > tmp)
                        tmp = r[j][i];
                }
                ans += tmp;
            }
            printf("%d\n", ans);
        } else {
            ans = 0;
            dfs(0, k);
            printf("%d\n", ans);
        }
    }
    return 0;
}
