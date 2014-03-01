#include <stdio.h>
long long gcd(long long x, long long y) {
    static long long t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
inline long long ReadInt(long long *x) {
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
    int n, m, i, j;
    long long A[10000], sum, x, y, t;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        sum = 0;
        for(i = 0; i < n; i++) {
            for(j = 1; j < m; j++)
                ReadInt(&x);
            ReadInt(&A[i]);
            sum += A[i];
        }
        for(i = 0; i < n ; i++) {
            x = A[i], y = sum;
            t = gcd(x, y);
            x /= t, y /= t;
            printf("%lld / %lld\n", x, y);
        }
    }
    return 0;
}
