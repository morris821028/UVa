#include <stdio.h>
#include <string.h>
#define maxN 105
int map[101][101], ans;
int way[101];
int n, m, x, y;
void DFS(int last, int now) {
    int i, j;
    for(i = 0; i < now; i++)
            for(j = 0; j < now; j++)
                if(map[way[i]][way[j]] == 0)
                    return ;
    if(now > ans ) {
        ans = now;
    }
    for(i = last; i < n; i++) {
        way[now] = i;
        DFS(i+1, now+1);
        way[now] = 0;
    }
}/*
6 5
0 1
1 2
1 3
1 4
2 3
3 4
*/
int main() {
    while(scanf("%d %d", &m, &n) == 2) {
        memset(map, 0, sizeof(map));
        for(int i = 0; i < n; i++)
            map[i][i] = 1;
        while(m--) {
            scanf("%d %d", &x, &y);
            map[x][y] = 1;
            map[y][x] = 1;
        }
        ans = 0;
        DFS(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
