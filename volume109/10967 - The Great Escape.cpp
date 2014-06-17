#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define oo 0xfffffff
using namespace std;
typedef struct {
    int x, y;
} Pt;
char g[1005][1005];
int D, n, m;
int dp[1005][1005][4];
void spfa() {
    int i, j, k, x, y, tx, ty, sa;
    Pt p;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            for(k = 0; k < 4; k++)
                if(i != n-1 || j != 0)
                    dp[i][j][k] = oo;
    queue<Pt> Q;
    p.x = n-1, p.y = 0;
    Q.push(p);
    int dd[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
    while(!Q.empty()) {
        p = Q.front();
        x = p.x, y = p.y;
        Q.pop();
        if(g[x][y] == '#')  continue;
        if(g[x][y] == '.') {
            for(k = 0; k < 4; k++) {
                for(i = 0; i < 4; i++) {
                    tx = x+dd[i][0], ty = y+dd[i][1];
                    if(tx < 0 || tx >= n || ty < 0 || ty >= m)
                        continue;
                    if(dp[tx][ty][i] > dp[x][y][k]+1) {
                        dp[tx][ty][i] = dp[x][y][k]+1;
                        p.x = tx, p.y = ty;
                        Q.push(p);
                    }
                }
            }
        } else {
            if(g[x][y] == 'N')  k = 0;
            else if(g[x][y] == 'E')  k = 1;
            else if(g[x][y] == 'S')  k = 2;
            else k = 3;
            for(i = 0; i < 4; i++) {
                tx = x+dd[i][0], ty = y+dd[i][1];
                if(tx < 0 || tx >= n || ty < 0 || ty >= m)
                    continue;
                int tmp = abs(i-k);
                if(tmp == 3)    tmp = 1;
                if(i == 0)  sa = 2;
                else if(i == 1) sa = 3;
                else if(i == 2) sa = 0;
                else sa = 1;
                if(dp[tx][ty][sa] > dp[x][y][k]+1+D*tmp) {
                    dp[tx][ty][sa] = dp[x][y][k]+1+D*tmp;
                    p.x = tx, p.y = ty;
                    Q.push(p);
                }
            }
        }
    }
    int ans = oo;
    for(i = 0; i < 4; i++)
        if(dp[0][m-1][i] < ans)
            ans = dp[0][m-1][i];
    if(ans != oo)
        printf("%d\n", ans);
    else
        puts("Poor Kianoosh");
}
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        scanf("%d", &D);
        spfa();
    }
    return 0;
}
