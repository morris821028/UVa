#include <stdio.h>

int k, n, m, ans;
void dfs(int x, int y, int k) {
    if(k == 0)
        return ;
    if(x-k <= n && x+k >= n && y-k <= m && y+k >= m)
        ans++;
    dfs(x+k, y+k, k/2);
    dfs(x+k, y-k, k/2);
    dfs(x-k, y+k, k/2);
    dfs(x-k, y-k, k/2);
}
int main() {
    while(scanf("%d %d %d", &k, &n, &m) == 3) {
        if(k == 0 && n == 0 && m == 0)
            break;
        ans = 0;
        dfs(1024, 1024, k);
        printf("%3d\n", ans);
    }
    return 0;
}
