#include <stdio.h>
#include <string.h>
#define mod 1000000007
#define maxL (1000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int pfactor[1000005], pfactorn[1000005], next[1000005];
int mapped[1000005], count[80000];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    int pt = 0;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            mapped[i] = pt;
            pt++;
            for(k = n/i, j = i*k; k >= i; k--, j -= i) {
                pfactor[j] = i;
                SET(j);
            }
            pfactor[i] = i;
        }
    }
    for(i = 2; i <= n; i++) {
        j = i, k = pfactor[i];
        while(j%k == 0)
            pfactorn[i]++, j /= k;
        next[i] = j;
    }
}
long long mpow(long long x, long long y, long long MOD) {
    if(y == 0)  return 1;
    if(y&1)
        return (x*mpow((x*x)%mod, y>>1, MOD))%MOD;
    return mpow((x*x)%MOD, y>>1, MOD);
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
    int testcase, cases = 0, n, D;
    ReadInt(&testcase);
    //scanf("%d", &testcase);
    while(testcase--) {
        ReadInt(&n);
        //scanf("%d", &n);
        long long ret = 1, sum = 0;
        int neg;
        memset(count, 0, sizeof(count));
        while(n--) {
            ReadInt(&D);
            //scanf("%d", &D);
            if(D < 0)   neg = 1, D = -D;
            else        neg = 0;
            while(D > 1) {
               // printf("%d ^ %d\n", pfactor[D], pfactorn[D]);
                int &v = count[mapped[pfactor[D]]];
                ret = (ret * mpow(v+1, mod-2, mod))%mod;
                if(neg) v -= pfactorn[D];
                else    v += pfactorn[D];
                ret = (ret * (v+1))%mod;
                D = next[D];
            }
            sum = sum + ret;
            if(sum >= mod)  sum -= mod;
        }
        printf("Case %d: %lld\n", ++cases, sum);
    }
    return 0;
}
