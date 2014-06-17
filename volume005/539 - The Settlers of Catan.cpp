#include <stdio.h>
#include <string.h>
int n, m, ans;
int map[30][30];
void dfs(int nd, int l) {
    if(l > ans)
        ans = l;
    int i;
    for(i = 0; i < n; i++) {
        if(map[nd][i]) {
            map[nd][i] = 0;
            map[i][nd] = 0;
            dfs(i, l+1);
            map[nd][i] = 1;
            map[i][nd] = 1;
        }
    }
}
int main() {
    int x, y, i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        memset(map, 0, sizeof(map));
        while(m--) {
            scanf("%d %d", &x, &y);
            map[x][y] = 1;
            map[y][x] = 1;
        }
        ans = 0;
        for(i = 0; i < n; i++)
            dfs(i, 0);
        printf("%d\n", ans);
    }
    return 0;
}
