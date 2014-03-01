#include <stdio.h>
#include <string.h>
#define GET(x) (used[(x)>>5]>>((x)&31)&1)
#define SET(x) (used[(x)>>5] |= 1<<((x)&31))
int dp[1<<10][10000], cnt[10];
int n, D, d[15];
int used[320005];
//char used[1<<10][10000];
char s[50];
int DP(int used_mask, int remainder) {
    if(GET(used_mask*10000+remainder))
        return dp[used_mask][remainder];
    if(used_mask == (1<<n)-1)
        return remainder == 0;
    int i, sum = 0;
    for(i = 0; i < n; i++) {
        if(!((used_mask>>i)&1)) {
            sum += DP(used_mask|(1<<i), (remainder*10+d[i])%D);
        }
    }
    dp[used_mask][remainder] = sum;
    SET(used_mask*10000+remainder);
    return sum;
}
int main() {
    int t, i;
    int f[15] = {1};
    for(i = 1; i < 15; i++)
        f[i] = f[i-1] * i;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %d", s, &D);
        memset(used, 0, sizeof(used));
        memset(cnt, 0, sizeof(cnt));
        n = strlen(s);
        for(i = 0; s[i]; i++)
            cnt[s[i]-'0']++, d[i] = s[i]-'0';
        int ans = DP(0, 0);
        for(i = 0; i < 10; i++)
            ans /= f[cnt[i]];
        printf("%d\n", ans);
    }
    return 0;
}
