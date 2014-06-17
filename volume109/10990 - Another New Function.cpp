#include <stdio.h>
#define maxL (2000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int phi[2000005];
int dep_phi[2000005];
int dp[2000005];
void sieve() {
    register int i, j;
    SET(1);
    int n = 2000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(j = i; j <= n; j += i) {
                phi[j] = phi[j]/i*(i-1);
                SET(j);
            }
        }
    }
}
int main() {
    int i, j, k;
    for(i = 2; i <= 2000000; i++)
        phi[i] = i;
    sieve();
    for(i = 2; i <= 2000000; i++) {
        dep_phi[i] = 1 + dep_phi[phi[i]];
        dp[i] = dp[i-1] + dep_phi[i];
    }
    scanf("%*d");
    while(scanf("%d %d", &i, &j) == 2)
        printf("%d\n", dp[j]-dp[i-1]);
    return 0;
}
