#include <stdio.h>
#define LL long long
#define mod 10007
LL mpow(LL a, LL b) {
    if(b == 0)  return 1;
    if(b&1)
        return a*mpow(a*a%mod, b/2)%mod;
    return mpow(a*a%mod, b/2);
}
int P[1001][1001];
int main() {
    LL a, b, k, n, m;
    scanf("%lld %lld %lld %lld %lld", &a, &b, &k, &n, &m);
    LL res;
    P[0][0] = 1;
    for(int i = 0; i <= k; i++) {
        P[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            P[i][j] = P[i-1][j]+P[i-1][j-1];
            if(P[i][j] >= mod)  P[i][j] %= mod;
        }
    }
    res = mpow(a, n)*mpow(b, m)%mod;
    res = res*P[k][n]%mod;
    printf("%lld\n", res);
    return 0;
}
