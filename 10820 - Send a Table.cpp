#include <stdio.h>
int p[5500], pt = 0;
void sieve() {
    char mark[32767] = {};
    int i, j;
    for(i = 2; i < 32767; i++)
        if(!mark[i]) {
            p[pt++] = i;
            for(j = i+i; j < 32767; j += i)
                mark[j] = 1;
        }
}
int sol(int n) {
    static int a, b, i;
    a = 1, b = n;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            a *= p[i]-1;
            b /= p[i];
            n /= p[i];
            while(n%p[i] == 0)
                n /= p[i];
        }
    }
    if(n != 1)
        a *= n-1, b /= n;
    return a*b;
}
int main() {
    int n;
    sieve();
    int dp[50001] = {0,1}, i;
    for(i = 2; i <= 50000; i++)
        dp[i] = dp[i-1] + sol(i)*2;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d\n", dp[n]);
    }
    return 0;
}
