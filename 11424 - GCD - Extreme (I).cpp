#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxL (200000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int phi[200005];
long long dp[200005];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 200000;
    for(i = 2; i <= n; i++)
        phi[i] = i;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            phi[i] = phi[i]/i*(i-1);
            for(k = n/i, j = i*k; k >= 2; k--, j -= i) {
                SET(j);
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}
int main() {
    sieve();
    int n;
    register int i, j, *k;
    for(i = 1; i <= 200000; i++) { // gcd(n, ?) = i
        k = phi+2;
        for(j = i+i; j <= 200000; j += i) {// j = n
            //dp[j] += i*phi[j/i];
            dp[j] += i*(*k);
            k++;
        }
    }
    for(i = 1; i <= 200000; i++)
        dp[i] += dp[i-1];
    while(scanf("%d", &n) == 1 && n) {
        printf("%lld\n", dp[n]);
    }
    return 0;
}
