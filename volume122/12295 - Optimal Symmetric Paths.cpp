#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#define mod 1000000009
using namespace std;
int n, g[105][105];
int dp[105][105], cnt[105][105], path[105][105];
int inq[105][105];
int dfs(int x, int y) {
    int &v = path[x][y];
    if(inq[x][y])  return v;
    inq[x][y] = 1;
    if(x+1 < n && dp[x][y] == dp[x+1][y]+g[x][y])
        v += dfs(x+1, y);
    if(v >= mod)    v -= mod;
    if(x-1 >= 0 && dp[x][y] == dp[x-1][y]+g[x][y])
        v += dfs(x-1, y);
    if(v >= mod)    v -= mod;
    if(y+1 < n && dp[x][y] == dp[x][y+1]+g[x][y])
        v += dfs(x, y+1);
    if(v >= mod)    v -= mod;
    if(y-1 >= 0 && dp[x][y] == dp[x][y-1]+g[x][y])
        v += dfs(x, y-1);
    if(v >= mod)    v -= mod;
    return v;
}
int main() {
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        for(i = 0; i < n; i++)
            for(j = 0; i+j+1 < n; j++)
                g[i][j] += g[n-j-1][n-i-1];
        memset(dp, 63, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));
        memset(inq, 0, sizeof(inq));
        memset(path, 0, sizeof(path));
        dp[0][0] = g[0][0], cnt[0][0] = 1;
        path[0][0] = 1;
        queue<int> X, Y;
        int x, y, tx, ty;
        int dx[] = {0,0,1,-1};
        int dy[] = {1,-1,0,0};
        X.push(0), Y.push(0);
        while(!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            inq[x][y] = 0;
            if(x + y == n-1)    continue;
            for(i = 0; i < 4; i++) {
                tx = x+dx[i], ty = y+dy[i];
                if(tx < 0 || ty < 0 || tx >= n || ty >= n)  continue;
                if(dp[tx][ty] > dp[x][y] + g[tx][ty]) {
                    dp[tx][ty] = dp[x][y] + g[tx][ty];
                    if(inq[tx][ty] == 0) {
                        inq[tx][ty] = 1;
                        X.push(tx), Y.push(ty);
                    }
                }
            }
        }
        int mn = 0xfffffff, ret = 0;
        for(i = 0; i < n; i++)
            mn = min(mn, dp[i][n-i-1]);
        memset(inq, 0, sizeof(inq));
        inq[0][0] = 1;
        for(i = 0; i < n; i++) {
            if(dp[i][n-i-1] == mn) {
                ret += dfs(i, n-i-1);
                if(ret >= mod)
                    ret -= mod;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
