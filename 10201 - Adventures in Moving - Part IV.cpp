#include <stdio.h>
#include <algorithm>
#define oo 100000000
using namespace std;

int main() {
    int t, D;
    int i, j, dp[105][205];
    char s[105];
    scanf("%d", &t);
    while(getchar() != '\n');
    gets(s);
    while(t--) {
        scanf("%d", &D);
        while(getchar() != '\n');
        int d[105], p[105], n = 1;
        d[0] = 0, p[0] = 0;
        while(gets(s) && s[0]) {
            sscanf(s, "%d %d", &d[n], &p[n]);
            n++;
        }
        d[n] = D, p[n] = oo;
        for(i = 0; i <= n; i++)
            for(j = 0; j <= 200; j++)
                dp[i][j] = oo;
        dp[0][100] = 0;
        for(i = 1; i <= n; i++) {
            int dis = d[i]-d[i-1];
            for(j = dis; j <= 200; j++)
                dp[i][j-dis] = min(dp[i][j-dis], dp[i-1][j]);
            for(j = 1; j <= 200; j++)
                dp[i][j] = min(dp[i][j], dp[i][j-1]+p[i]);
        }
        int ans = oo;
        for(i = 100; i <= 200; i++)
            ans = min(ans, dp[n][i]);
        if(ans == oo)
            puts("Impossible");
        else
            printf("%d\n", ans);
        if(t)
            puts("");
    }
    return 0;
}
