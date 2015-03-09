#include <stdio.h>
#include <algorithm>
using namespace std;
#define oo 1LL<<60
int main() {
    int t, n;
    long long x, dp[10000][3][3];
    /* [012],[012] ¥Ï§À¦¸¼Æ ´á®ð*/
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int i, j, k;
        for(i = 0; i < n; i++)
            for(j = 0; j < 3; j++)
                for(k = 0; k < 2; k++)
                    dp[i][j][k] = oo;
        scanf("%lld", &x);
        dp[0][0][0] = 2*x;
        for(i = 1; i < n; i++) {
            scanf("%lld", &x);
            for(j = 0; j < 3; j++) {
                for(k = 0; k < 3; k++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k]+5+2*x);
                    if(j-1 >= 0) //¶È¥Ï
                        dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][k]+10+2*x);
                    if(k+1 < 2)  //¶È¼Q
                        dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k+1]+5+x);
                    if(j-1 >= 0 && k+1 < 2) //¥Ï«á¼Q
                        dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][k+1]+10+x);
                }
            }
            dp[i][0][0] = min(dp[i][0][0], dp[i-1][2][0]+10+x);
            dp[i][0][1] = min(dp[i][0][1], dp[i-1][2][0]+10+2*x);
            dp[i][0][1] = min(dp[i][0][1], dp[i-1][2][1]+10+x);
            dp[i][0][2] = min(dp[i][0][2], dp[i-1][2][1]+10+2*x);
        }
        long long res = oo;
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                res = min(res, dp[n-1][i][j]);
        printf("%lld\n", res);
    }
    return 0;
}
