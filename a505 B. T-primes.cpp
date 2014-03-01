#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LL long long
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
main() {
    sieve();
    int t;
    LL n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n), m = sqrt(n);
        if(m*m != n || GET(m))
            puts("NO");
        else    puts("YES");
    }
    return 0;
}
