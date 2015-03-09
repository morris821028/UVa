#include <stdio.h>
#include <algorithm>
using namespace std;
#define oo 2147483647
int g[305][105];
int main() {
    int t, n, m;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%d", &g[i][j]);
                g[i+n][j] = g[i][j];
                g[i+n*2][j] = g[i][j];
            }
        }
        int dp[305][105];
        n = n*3;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                dp[i][j] = oo;
                //printf("%d ", g[i][j]);
            }
            //puts("");
        }
        for(i = 0; i < n; i++)
            if(g[i][0] > 0)
                dp[i][0] = min(dp[i][0], g[i][0]);
        for(j = 0; j < m; j++) {
            for(i = 0; i < n; i++) {
                if(dp[i][j] == oo)  continue;
                if(g[i][j+1] > 0)
                    dp[i][j+1] = min(dp[i][j+1], dp[i][j]+g[i][j+1]);
                if(g[i+1][j+1] > 0)
                    dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+g[i+1][j+1]);
                if(g[i-1][j+1] > 0)
                    dp[i-1][j+1] = min(dp[i-1][j+1], dp[i][j]+g[i-1][j+1]);

            }
        }
        int ans = oo;
        for(i = 0; i < n; i++) {
            ans = min(ans, dp[i][m-1]);
        }
        if(ans == oo)
            puts("-1");
        else
            printf("%d\n", ans);
    }
    return 0;
}
/*
2
3 4
5 0 2 8
4 9 0 1
7 3 6 0
6 6
1 2 0 4 5 6
1 2 0 0 5 0
0 2 3 0 5 6
1 0 3 0 5 6
1 2 0 0 5 6
1 2 0 4 5 6
*/
