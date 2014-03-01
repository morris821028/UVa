#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LL long long
#define maxL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL], p[5500], pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            p[pt++] = i;
        }
    }
}
int sol(int A, int C) {
    int i, B = 1;
    int t1, t2;
    for(i = 0; i < pt && p[i]*p[i] <= C; i++) {
        if(C%p[i] == 0) {
            t1 = 1, t2 = 1;
            while(C%p[i] == 0)
                C /= p[i], t1 *= p[i];
            while(A%p[i] == 0)
                A /= p[i], t2 *= p[i];
            if(t1 > t2)
                B *= t1;
        }
    }
    if(C != 1 && A == 1)
        B *= C;
    return B;
}
main() {
    sieve();
    int t, A, C;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &A, &C);
        if(C%A)
            puts("NO SOLUTION");
        else
            printf("%d\n", sol(A, C));
    }
    return 0;
}
