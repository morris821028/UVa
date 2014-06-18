#include <stdio.h>
#include <string.h>
int map[11][11], ans, n;
int used[11][11];
void DFS(int x, int y, int l) {
    if(x <= 0 || y <= 0 || x > n || y > n)
        return ;
    if(map[x][y] == 1 || used[x][y] == 1)
        return ;
    used[x][y] = 1;
    ans ++;
    DFS(x+1, y, l+1);
    DFS(x-1, y, l+1);
    DFS(x, y+1, l+1);
    DFS(x, y-1, l+1);
}
int main() {
    int t, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        memset(map, 0, sizeof(map));
        memset(used, 0, sizeof(used));
        int sx, sy;
        while(m--) {
            scanf("%d %d", &sx, &sy);
            map[sx][sy] = 1;
        }
        scanf("%d %d", &sx, &sy);
        ans = 0;
        DFS(sx, sy, 1);
        printf("%d\n", ans);
    }
    return 0;
}
