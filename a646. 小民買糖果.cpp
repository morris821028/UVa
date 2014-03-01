#include <stdio.h>
#include <string.h>
int dp[1000], a, b;
int shift[1000], shift_v[1000];
char used[1000];
int build(int n) {
    if(n == 0)
        return 0;
    if(used[n])
        return dp[n];
    int i, v, tmp;
    dp[n] = 0;
    for(i = shift[n]; i >= 1; i = shift[i-1]) {
        v = shift_v[i];
        tmp = build(v+n-i) + v;
        if(tmp > dp[n])
            dp[n] = tmp;
    }
    used[n] = 1;
    return dp[n];
}
int main() {
    int n, i, j, k;
    char s[50];
    while(scanf("%d %s", &n, &s) == 2) {
        for(i = 2, a = 0, b = 1; s[i]; i++)
            b *= 10, a = a*10 + s[i]-'0';
        for(i = 1; i <= n; i++)
            shift_v[i] = i*a/b;
        for(i = n, k = n; i >= 0; i--) {
            if(i == 0 || shift_v[i] != shift_v[i-1]) {
                for(j = i; j <= k; j++)
                    shift[j] = i;
                k = i-1;
            }
        }
        memset(used, 0, sizeof(used));
        printf("%d\n", build(n)+n);
    }
    return 0;
}
// 69 0.143
// 84 0.167
