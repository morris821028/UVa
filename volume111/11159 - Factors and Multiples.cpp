#include <stdio.h>
#include <string.h>
int g[1005][1005], gt[1005];
int mx[1005], my[1005], used[1005];
int dfs(int nd) {
    int i, a;
    for(i = 0; i < gt[nd]; i++) {
        a = g[nd][i];
        if(!used[a]) {
            used[a] = 1;
            if(my[a] < 0 || dfs(my[a])) {
                mx[nd] = a, my[a] = nd;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int t, cases = 0, n, m, i, j;
    int A[505], B[505];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)  scanf("%d", &A[i]);
        scanf("%d", &m);
        for(i = 0; i < m; i++)  scanf("%d", &B[i]);
        memset(gt, 0, sizeof(gt));
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(B[j] == 0 || (A[i] && B[j]%A[i] == 0)) {
                    g[i][gt[i]++] = n+j;
                }
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            if(mx[i] < 0) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    ans++;
            }
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
