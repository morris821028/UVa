#include <stdio.h>
short dp[1000005];
int res[1000005];
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    for(i = 2; i <= 1000; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i) {
                SET(j);
                dp[j] = i;
            }
        }
    }
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    sieve();
    int mx_n = 1, mx_v = 1;
    int i, j, k, n, t;
    dp[1] = 1, res[1] = 1;
    for(i = 2; i <= 1000000; i++) {
        if(dp[i] == 0) {
            dp[i] = 2;
        } else {
            j = i, k = dp[i], n = 0;
            while(j%k == 0)
                j /= k, n++;
            dp[i] = dp[j] * (n+1);
        }
        if(dp[i] >= mx_n)
            mx_n = dp[i], mx_v = i;
        res[i] = mx_v;
    }
    ReadInt(&t);
    //scanf("%d", &t);
    while(t--) {
        ReadInt(&n);
        //scanf("%d", &n);
        printf("%d\n", res[n]);
    }
    return 0;
}
