#include <stdio.h>
#include <string.h>
int ans = 0, n, m;
int g[105][105], gt[105];
int used[105] = {};
void dfs(int idx, int v) {
    if(v > ans) ans = v;
    if(v + n-idx < ans)
        return;
    if(idx == n)
        return;
    int i = 0, can = 0;
    for(i = 0; i < gt[idx]; i++) {
        if(used[g[idx][i]])
            break;
    }
    if(i == gt[idx])    can = 1;
    if(can) {
        used[idx] = 1;
        dfs(idx+1, v+1);
        used[idx] = 0;
    }
    dfs(idx+1, v);
}
int main() {
    int i, x, y;
    while(scanf("%d %d", &m, &n) == 2) {
        for(i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            g[x][gt[x]++] = y;
            g[y][gt[y]++] = x;
        }
        ans = 0;
        dfs(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
