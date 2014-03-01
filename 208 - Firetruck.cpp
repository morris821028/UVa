#include <stdio.h>
#include <string.h>
int E, g[25][25], path[25];
int visited[25], pathcnt = 0;
int check(int st) {
    int Q[25], Qt, i, j, used[25] = {}, tn;
    Q[Qt = 0] = st;
    for(i = 0; i <= Qt; i++) {
        tn = Q[i];
        if(tn == E) return 0;
        for(j = 1; j <= 21; j++) {
            if(visited[j] == 0 && g[tn][j] && used[j] == 0)
                used[j] = 1, Q[++Qt] = j;
        }
    }
    return 1;
}
void dfs(int nd, int dep) {
    int i;
    if(nd == E) {
        pathcnt++;
        printf("1");
        for(i = 0; i < dep; i++)
            printf(" %d", path[i]);
        puts("");
        return;
    }
    for(i = 1; i <= 21; i++) {
        if(g[nd][i] && visited[i] == 0) {
            if(check(i))
                continue;
            visited[i] = 1;
            path[dep] = i;
            dfs(i, dep+1);
            visited[i] = 0;
        }
    }
}
int main() {
    int cases = 0, x, y;
    int i;
    while(scanf("%d", &E) == 1) {
        memset(g, 0, sizeof(g));
        memset(visited, 0, sizeof(visited));
        while(scanf("%d %d", &x, &y) == 2 && x)
            g[x][y] = g[y][x] = 1;
        printf("CASE %d:\n", ++cases);
        pathcnt = 0;
        visited[1] = 1;
        dfs(1, 0);
        printf("There are %d routes from the firestation to streetcorner %d.\n", pathcnt, E);
    }
    return 0;
}
