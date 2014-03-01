#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LL long long
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL], p[100000], pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            p[pt++] = i;
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
int check(int n) {
    int i, j;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            j = n/p[i];
            if(!GET(j)) return 1;
        }
    }
    return 0;
}
int main() {
    sieve();
    int n;
    while(scanf("%d", &n) == 1) {
        int ans = 0, i, val;
        for(i = 0; i < n; i++) {
            scanf("%d", &val);
            if(check(val))
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
