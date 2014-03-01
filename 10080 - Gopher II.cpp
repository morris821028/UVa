#include <stdio.h>
#include <string.h>
#include <math.h>
int map[202][202], mt[202];
int mx[202], my[202], used[202];
int dfs(int x) {
    int i, y;
    for(i = 0; i < mt[x]; i++) {
        y = map[x][i];
        if(!used[y]) {
            used[y] = 1;
            if(my[y] == 0 || dfs(my[y])) {
                mx[x] = y, my[y] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int n, m, s, v, i, j;
    while(scanf("%d %d %d %d", &n, &m, &s, &v) == 4) {
        double g[101][2], h[101][2];
        for(i = 1; i <= n; i++)
            scanf("%lf %lf", &g[i][0], &g[i][1]);
        for(i = 1; i <= m; i++)
            scanf("%lf %lf", &h[i][0], &h[i][1]);
        memset(mt, 0, sizeof(mt));
        memset(mx, 0, sizeof(mx));
        memset(my, 0, sizeof(my));

        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                if(sqrt((g[i][0]-h[j][0])*(g[i][0]-h[j][0])+
                        (g[i][1]-h[j][1])*(g[i][1]-h[j][1]))/v <= s) {
                    map[i][mt[i]++] = n+j;
                }
            }
        }
        int ans = 0;
        for(i = 1; i <= n; i++) {
            if(!mx[i]) {
                memset(used, 0, sizeof(used));
                if(dfs(i))
                    ans++;
            }
        }
        printf("%d\n", n-ans);
    }
    return 0;
}
