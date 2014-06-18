#include <stdio.h>
int g[105][105], used[105], n;
int f[105][105];
void dfs(int nd, int st) {
    if(nd == st)    return ;
    int i;
    used[nd] = 1;
    for(i = 0; i < n; i++) {
        if(g[nd][i] && !used[i]) {
            dfs(i, st);
        }
    }
}
int main() {
    int t, i, j, k;
    int cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        int fused[105] = {};
        for(i = 0; i < n; i++)
            used[i] = 0;
        dfs(0, -1);
        for(i = 0; i < n; i++)
            fused[i] = used[i];
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                used[j] = 0;
            dfs(0, i);
            for(j = 0; j < n; j++)
                if(fused[j] && !used[j])
                    f[i][j] = 1;
                else
                    f[i][j] = 0;
            f[i][i] = fused[i];

        }
        printf("Case %d:\n", ++cases);
        putchar('+');
        for(i = -n+1; i < n; i++)
            putchar('-');
        puts("+");
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                putchar('|');
                putchar(f[i][j] ? 'Y' : 'N');
            }
            puts("|");
            putchar('+');
            for(j = -n+1; j < n; j++)
                putchar('-');
            puts("+");
        }
    }
    return 0;
}
