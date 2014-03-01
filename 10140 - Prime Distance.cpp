#include <stdio.h>
#include <math.h>
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5]|=1<<(x&31))
int mark[maxL];
int p[700000], pt = 0;
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
int isprime(int n) {
    if(n < 1000000)
        return !GET(n);
    static int sq, i;
    sq = (int)sqrt(n);
    for(i = 0; i < pt && p[i] <= sq; i++)
        if(n%p[i] == 0)
            return 0;
    return 1;
}
int main() {
    sieve();
    int L, U;
    while(scanf("%d %d", &L, &U) == 2) {
        long long i;
        int last = -1, p1, p2, p3, p4;
        int flag = 0;
        int close = 2147483647, dist = -close;
        for(i = L; i <= U; i++) {
            if(isprime(i)) {
                if(last == -1)
                    last = i;
                else {
                    if(i-last < close) {
                        close = i-last;
                        p1 = last, p2 = i;
                    }
                    if(i-last > dist) {
                        dist = i-last;
                        p3 = last, p4 = i;
                    }
                    last = i;
                    flag = 1;
                }
            }
        }
        if(flag == 0)
            puts("There are no adjacent primes.");
        else {
            printf("%d,%d are closest, %d,%d are most distant.\n", p1, p2, p3, p4);
        }
    }
    return 0;
}
