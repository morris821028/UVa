#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxL (10000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL], p[5000], pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            p[pt++] = i;
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
int isprime(int n) {
    if(n < 2)  return 0;
    static int sq, i;
    sq = (int)sqrt(n);
    for(i = 0; i < pt && p[i] <= sq; i++)
        if(n%p[i] == 0)
            return 0;
    return 1;
}
int main() {
    sieve();
    int n, i;
    while(scanf("%d", &n) == 1) {
        printf("%d is ", n);
        if(n&1) {
            if(isprime(n-2)) {
                printf("the sum of 2 and %d.\n", n-2);
            } else {
                puts("not the sum of two primes!");
            }
        } else {
            int flag = 0;
            for(i = n/2-1; i >= 0; i--) {
                if(isprime(i) && isprime(n-i)) {
                    printf("the sum of %d and %d.\n", i, n-i);
                    flag = 1;
                    break;
                }
            }
            if(!flag)
                puts("not the sum of two primes!");
        }
    }
    return 0;
}
