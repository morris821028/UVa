#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define maxL (1000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int phi[1000005];
double dp[1000005], sum[1000005];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
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
    register int i, j;
    for(i = 1; i <= 1000000; i++) { // gcd(n, ?) = i
        for(j = i+i; j <= 1000000; j += i) {// j = n
            dp[j] += log10(i) * phi[j/i];            
        }
    }
    for(i = 1; i <= 1000000; i++) {
        dp[i] += dp[i-1];
        sum[i] = sum[i-1] + log10(i);
    }
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
    	double f;
    	f = sum[n] * (n-1) - dp[n];
        printf("Case %d: %.0f %.0f\n", ++cases, floor(dp[n]/100.0) + 1, floor(f/100.0) + 1);
    }
    return 0;
}

