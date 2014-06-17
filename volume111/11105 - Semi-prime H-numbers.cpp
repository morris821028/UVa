#include <stdio.h>
#include <string.h>
#define maxL (1000005>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int hp[100000], hpt = 0;
int dp[1000005] = {};
void hsieve() {
    int i, j, k;
    int n = 1000005;
    for(i = 5; i <= n; i += 4) {
        if(!GET(i)) {
            hp[hpt++] = i;
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
void hbuild() {
    memset(mark, 0, sizeof(mark));
    int i, j, k;
    for(i = 0; hp[i]*hp[i] <= 1000001; i++) {
        for(j = 0; j < hpt; j++) {
            k = hp[i]*hp[j];
            if(k > 1000001) break;
            if(((k-1)&3) == 0)
                SET(k);
        }
    }
    for(i = 1; i <= 1000001; i++)
        dp[i] = dp[i-1] + (GET(i) != 0);
}
int main() {
    hsieve();
    hbuild();
    int n;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d %d\n", n, dp[n]);
    }
    return 0;
}
