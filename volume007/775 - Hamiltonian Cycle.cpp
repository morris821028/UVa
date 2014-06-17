#include <stdio.h>
#include <algorithm>
using namespace std;
int g[512][512], gt[512];
int path[512], flag, n;
int Q[512], Qt, i, j, tn;
char used2[512], used[512];
int check(int st, int cnt) {
    Q[Qt = 0] = st;
    for(i = 1; i <= n; i++)
        used2[i] = 0;
    used2[st] = 1;
    for(i = 0; i <= Qt; i++) {
        tn = Q[i];
        for(j = 0; j < gt[tn]; j++) {
            if(!used2[g[tn][j]] && !used[g[tn][j]]) {
                Q[++Qt] = g[tn][j];
                used2[g[tn][j]] = 1;
            }
        }
    }
    return cnt+Qt == n;
}
void dfs(int nd, int dep) {
    if(!flag)   return;
    int i;
    if(dep == n+1 && nd == 1) {
        printf("%d", path[0]);
        for(i = 1; i < dep; i++)
            printf(" %d", path[i]);
        puts("");
        flag = 0;
        return;
    }
    for(i = 0; i < gt[nd]; i++) {
        if(!used[g[nd][i]] && check(g[nd][i], dep)) {
            path[dep] = g[nd][i];
            used[g[nd][i]] = 1;
            dfs(g[nd][i], dep+1);
            used[g[nd][i]] = 0;
        }
    }
}
int main() {
    int i, x, y;
    char s[500];
    while(scanf("%d", &n) == 1) {
        while(getchar() != '\n');
        for(i = 1; i <= n; i++)
            gt[i] = 0, used[i] = 0;
        while(gets(s) && s[0] != '%') {
            sscanf(s, "%d %d", &x, &y);
            if(x == y)  continue;
            if(x > n || y > n)
                continue;
            g[x][gt[x]++] = y;
            g[y][gt[y]++] = x;
        }
        path[0] = 1, flag = 1;
        for(i = 1; i <= n; i++)
            sort(g[i], g[i]+gt[i]);
        dfs(1, 1);
        if(flag)
            puts("N");
    }
    return 0;
}
