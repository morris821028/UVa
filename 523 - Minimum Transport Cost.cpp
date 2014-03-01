#include <stdio.h>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int t;
    char s[505];
    int g[505][505], gv[505];
    scanf("%d", &t);
    while(getchar() != '\n');
    while(getchar() != '\n');
    while(t--) {
        gets(s);
        stringstream sin(s);
        int n = 1, x, y, i, j;
        while(sin >> g[1][n])
            n++;
        n--;
        for(i = 2; i <= n; i++)
            for(j = 1; j <= n; j++)
                scanf("%d", &g[i][j]);
        for(i = 1; i <= n; i++)
            scanf("%d", &gv[i]);
        while(getchar() != '\n');
        int pflag = 0;
        while(gets(s) && s[0]) {
            if(pflag)   puts("");
            pflag = 1;
            int st, ed;
            int dis[505] = {}, used[505] = {}, prev[505];
            sscanf(s, "%d %d", &st, &ed);
            for(i = 1; i <= n; i++)
                dis[i] = 0xfffffff;
            dis[st] = 0;
            queue<int> Q;
            Q.push(st);
            while(!Q.empty()) {
                x = Q.front(), Q.pop();
                used[x] = 0;
                for(i = 1; i <= n; i++) {
                    if(g[x][i] == -1)
                        continue;
                    if(dis[i] > dis[x]+gv[i]+g[x][i]) {
                        dis[i] = dis[x]+gv[i]+g[x][i];
                        prev[i] = x;
                        if(used[i] == 0) {
                            used[i] = 1;
                            Q.push(i);
                        }
                    }
                }
            }
            printf("From %d to %d :\n", st, ed);
            int stk[105], stkidx = 0;
            x = ed;
            while(x != st) {
                stk[stkidx++] = x;
                x = prev[x];
            }
            printf("Path: %d", st);
            for(i = stkidx-1; i >= 0; i--)
                printf("-->%d", stk[i]);
            if(st == ed) {
                printf("-->%d", ed);
                dis[ed] = gv[ed];
            }
            puts("");
            printf("Total cost : %d\n", dis[ed]-gv[ed]);
        }
        if(t)
            puts("");
    }
    return 0;
}
