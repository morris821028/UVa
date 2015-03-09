#include <stdio.h>
#include <stdlib.h>
#define mod 100000007LL
#define LL long long
int A[1005][1005];
LL inv(LL a) {
    LL d = mod, x = 0, s = 1, q, r, t;
    while(a) {
        q = d / a, r = d % a;
        d = a, a = r;
        t = x - q * s, x = s, s = t;
    }
    if (d != 1) return -1;
    return (x + mod) % mod;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, m, q, i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        LL tot = 1, tmp;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                ReadInt(&A[i][j]);
                if(A[i][j] >= mod)
                    A[i][j] %= mod;
                tot *= A[i][j];
                if(tot >= mod)
                    tot %= mod;
            }
        }
        tot = (tot+mod)%mod;
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &i, &j), i--, j--;
            tmp = inv(A[i][j])*tot;
            if(tmp >= mod)
                tmp %= mod;
            printf("%lld\n", tmp);
        }
    }
    return 0;
}
