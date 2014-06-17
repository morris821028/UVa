#include <stdio.h>
#include <string.h>
char s[1000005];
int dp[3][1000005][3] = {};
/*[0][0],[1][0],[0][1],[2][0],[0][2]*/
int Mpow(int x, int y, int mod) {
    if(!y)  return 1;
    if(y&1)
        return (x*Mpow((x*x)%mod, y/2, mod))%mod;
    return Mpow((x*x)%mod, y/2, mod);
}
int main() {
    int n, m;
    int i, j;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    dp[0][0][0] = 1;
    dp[1][0][1] = 1;
    dp[2][0][2] = 1;
    for(i = 0; i <= n; i++) {
        for(j = 0; j < 3; j++) {
            dp[j][i+1][0] = dp[j][i][1];
            dp[j][i+1][1] = dp[j][i][0]+dp[j][i][2];
            dp[j][i+1][2] = dp[j][i][1];
        }
    }
    printf("%d\n", dp[0][3][0]+dp[0][3][1]+dp[0][3][2]);
    int line = 0, rk = 0, mn = 0;
    for(i = 0; i < n; i++) {
        if(s[i] == 'P') {
            if(mn == 0 && line == 0) {
                rk += dp[0][n-i][0]+dp[0][n-i][1]+dp[0][n-i][2]-1;
                int tmp = (n-i)/2;
                if((n-i)%2 == 0)    tmp--;
                rk += Mpow(2, tmp, 1000);
                printf("%d %d %d - %d\n", line, n-i, mn, i);
                printf("rk %d\n", rk);
            } else if(mn == -1 && line == 0){
                int tmp = (n-i)/2;
                if((n-i)%2 == 0)    tmp--;
                rk += Mpow(2, tmp, 1000);
                printf("rk %d %d\n", rk, n-i);
            } else if(mn == -1 && line == -1) {
                rk += dp[0][n-i][0]+dp[0][n-i][1]+dp[0][n-i][2]-1;
                int tmp = (n-i)/2;
                if((n-i)%2 == 0)    tmp--;
                rk += Mpow(2, tmp, 1000);
                printf("rk %d %d\n", rk, n-i);
            } else if(mn == 0 && line == 1) {
                rk += dp[0][n-i][0]+dp[0][n-i][1]+dp[0][n-i][2]-1;/*+Not*/
                rk += dp[1][n-i][0]+dp[1][n-i][1]+dp[1][n-i][2]-1;
                int tmp = (n-i)/2;
                if((n-i)%2 == 0)    tmp--;
                rk -= Mpow(2, tmp, 1000);
                printf("rk %d\n", rk);
            } else {
                printf("%d %d %d\n", line, mn, i);
            }
        }
        if(s[i] == 'L') line++;
        else line--;
        if(line < mn)   mn = line;
    }
    rk++;
    printf("%d\n", rk);
    return 0;
}
