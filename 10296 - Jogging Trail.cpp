#include <stdio.h>
#include <string.h>
#include <algorithm>
#define oo 0xffffff
using namespace std;
int g[15][15];
int dp[1<<15], odd[15];
char used[1<<15];
void floyd(int n) {
    int i, j, k;
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
}
int DP(int state, int n) {
    if(!state)  return 0;
    if(used[state]) return dp[state];
    int i, j, ans = oo;
    for(i = 0; i < n; i++) {
        if((state>>i)&1) {
            for(j = i+1; j < n; j++) {
                if((state>>j)&1) {
                    ans = min(ans, DP(state-(1<<i)-(1<<j), n)+g[odd[i]][odd[j]]);
                }
            }
            break;
        }
    }
    used[state] = 1;
    dp[state] = ans;
    return dp[state];
}
int main() {
    int n, m, i, j;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                g[i][j] = oo;
            g[i][i] = 0;
        }
        memset(dp, 0, sizeof(dp));
        memset(used, 0, sizeof(used));
        int sum = 0, x, y, w;
        int deg[16] = {};
        while(m--) {
            scanf("%d %d %d", &x, &y, &w);
            x--, y--;
            g[x][y] = min(g[x][y], w);
            g[y][x] = min(g[y][x], w);
            deg[x]++;
            deg[y]++;
            sum += w;
        }
        floyd(n);
        int ot = 0;
        for(i = 0; i < n; i++)
            if(deg[i]&1) {
                odd[ot++] = i;
            }
        printf("%d\n", sum + DP((1<<ot)-1, ot));
    }
    return 0;
}
