#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[1000005];
int dp[1000005][3] = {};
long long Mpow(long long x, long long y, long long mod) {
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
    dp[0][0] = 1;
    for(i = 0; i <= n; i++) {
        dp[i+1][0] = dp[i][1]%m;
        dp[i+1][1] = (dp[i][0]+dp[i][2])%m;
        dp[i+1][2] = (dp[i][1])%m;
    }
    int line = 0, rk = 0, mn = 0;
    for(i = 0; i < n; i++) {
        if(s[i] == 'P') {
            if(mn == line) {
                rk += dp[n-i][0]+dp[n-i][1]+dp[n-i][2]-1;
                int tmp = (n-i)/2;
                if((n-i)%2 == 0)    tmp--;
                rk += Mpow(2, tmp, m);
            } else if(abs(mn - line) == 1) {
                rk += dp[n-i-1][0]+dp[n-i-1][1]+dp[n-i-1][2];
                rk %= m;
            }
        }
        if(s[i] == 'L') line++;
        else line--;
        if(line < mn)   mn = line;
    }
    rk++;
    printf("%d\n", rk%m);
    return 0;
}
