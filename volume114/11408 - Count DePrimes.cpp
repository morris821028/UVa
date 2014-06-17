#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LL long long
#define maxL (5000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int cnt[5000001];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 5000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            cnt[i] = i;
            for(k = n/i, j = i*k; k >= i; k--, j -= i) {
                cnt[j] = i;
                SET(j);
            }
        }
    }
}
int dp[5000001] = {};
void build() {
    int i, j;
    for(i = 2; i <= 5000000; i++) {
        j = i;
        while(j%cnt[i] == 0)    j /= cnt[i];
        cnt[i] = cnt[j]+cnt[i];
        dp[i] = dp[i-1];
        if(!GET(cnt[i]))
            dp[i]++;
    }
}
int main() {
    sieve();
    build();
    int a, b;
    while(scanf("%d %d", &a, &b) == 2)
        printf("%d\n", dp[b]-dp[a-1]);
    return 0;
}
