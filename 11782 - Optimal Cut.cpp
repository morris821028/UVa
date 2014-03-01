#include <stdio.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
int H, K, i, j;
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
void dfs(int dep, short dp[]) {
    int v;
    ReadInt(&v);
    if(dep == H) {
        dp[1] = v;
        return;
    }
    short l[K+1], r[K+1];
    for(i = 1; i <= K; i++)
        l[i] = r[i] = -0xfff;
    dfs(dep+1, l);
    dfs(dep+1, r);
    for(i = 1; i <= K; i++) {
        for(j = K-i; j >= 1; j--) {
            dp[i+j] = max(dp[i+j], l[i]+r[j]);
        }
    }
    dp[1] = max(dp[1], v);
}
int main() {
    while(scanf("%d", &H), H >= 0) {
        scanf("%d", &K);
        short dp[K+1], ans = -0xfff;
        for(i = 0; i <= K; i++)
            dp[i] = -0xfff;
        dfs(0, dp);
        for(i = 1; i <= K; i++)
            ans = max(ans, dp[i]);
        printf("%hd\n", ans);
    }
    return 0;
}
