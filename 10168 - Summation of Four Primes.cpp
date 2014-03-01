#include <stdio.h>
#define maxL (10000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
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
void Goldbach(int n) {
    if(n == 4) {
        printf("2 2");
        return;
    }
    static int i;
    for(i = 3; ; i += 2) {
        if(!GET(i) && !GET(n-i)) {
            printf("%d %d", i, n-i);
            return;
        }
    }
}
int main() {
    sieve();
    int n;
    while(scanf("%d", &n) == 1) {
        if(n < 8) {
            puts("Impossible.");
            continue;
        }
        if(n&1)
            printf("2 3 "), n -= 5;
        else
            printf("2 2 "), n -= 4;
        Goldbach(n);
        puts("");
    }
    return 0;
}
