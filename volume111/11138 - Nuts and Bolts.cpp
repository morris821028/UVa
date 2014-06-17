#include <stdio.h>
#include <string.h>
int g[1005][1005], gt[1005];
int mx[1005], my[1005], used[1005];
int dfs(int now) {
    int i, x;
    for(i = 0; i < gt[now]; i++) {
        x = g[now][i];
        if(!used[x]) {
            used[x] = 1;
            if(my[x] == 0 || dfs(my[x])) {
                mx[now] = x, my[x] = now;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int n, m, i, j, x;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        memset(gt, 0, sizeof(gt));
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                scanf("%d", &x);
                if(x)
                    g[i][gt[i]++] = j+n;
            }
        }
        memset(mx, 0, sizeof(mx));
        memset(my, 0, sizeof(my));
        int ans = 0;
        for(i = 1; i <= n; i++) {
            if(!mx[i]) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    ans++;
            }
        }
        printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n", ++cases, ans);
    }
    return 0;
}
