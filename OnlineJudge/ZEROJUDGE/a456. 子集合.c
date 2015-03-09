#include <stdio.h>
int ans[16];
void dfs(int idx, int n, int m, int i) {
    if(idx == m) {
        printf("{%d", ans[0]);
        for(i = 1; i < m; i++)
            printf(",%d", ans[i]);
        puts("}");
        return;
    }
    for(; i <= n; i++) {
        ans[idx] = i;
        dfs(idx+1, n, m, i+1);
    }
}
int main() {
    int t, n, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        puts("{0}");
        for(i = 1; i <= n; i++)
            dfs(0, n, i, 1);
        if(t)
            puts("");
    }
    return 0;
}
