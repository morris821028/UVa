#include <stdio.h>
#include <string.h>
int gt[20], g[20][20];
int used[20] = {}, way[20];
int n, l, flag;
void dfs(int nd, int dep) {
    int i;
    if(dep == l) {
        flag = 1;
        printf("(1");
        for(i = 0; i < dep; i++)
            printf(",%d", way[i]);
        puts(")");
        return ;
    }
    for(i = 0; i < gt[nd]; i++) {
        if(!used[g[nd][i]]) {
            used[g[nd][i]] = 1;
            way[dep] = g[nd][i];
            dfs(g[nd][i], dep+1);
            used[g[nd][i]] = 0;
        }
    }
}
int main() {
    int i, j, x;
    int first = 0;
    while(scanf("%d %d", &n, &l) == 2) {
        if(first)   puts("");
        first = 1;
        memset(gt, 0, sizeof(gt));
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                scanf("%d", &x);
                if(x) {
                    g[i][gt[i]++] = j;
                }
            }
        }
        used[1] = 1;
        flag = 0;
        dfs(1, 0);
        used[1] = 0;
        if(!flag)
            printf("no walk of length %d\n", l);
        scanf("%d", &x);
    }
    return 0;
}
