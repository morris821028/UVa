#include <stdio.h>
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
int isprime(int n) {
    if(n > 10000000)
        puts("ERROR");
    return !GET(n);
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-') {
        if(c == '\n')   return -2;
        if(c == EOF) return EOF;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    if(c == '\n')   return 0;
    *x *= neg;
    return 1;
}
int main() {
    sieve();
    int A[100005];
    int cases = 0;
    while(1) {
        int flag = ReadInt(&A[0]);
        if(flag == -2) {
            puts("0");
            continue;
        } else if(flag < 0) break;
        long long sum = 0, ans = 0;
        int n = 1, i;
        if(flag == 1)
        do {
            int flag = ReadInt(&A[n]);
            if(flag == -2)   break;
            n++;
            if(flag == 0)   break;
        } while(1);
        for(i = 0; i < n; i++) {
            if(isprime(A[i])) {
                if(!i || A[i] > A[i-1])
                    sum += A[i];
                else {
                    if(sum > ans)   ans = sum;
                    sum = A[i];
                }
                if(sum > ans)   ans = sum;
            } else {
                sum = 0;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
