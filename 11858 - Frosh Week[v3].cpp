#include <stdio.h>
int A[1048576], X[1048576];
long long merge(int l, int m, int r) {
    if(l > m || m > r)
        return 0;
    int *L = A+l, *R = A+m+1;
    int *M = X;
    int *eL = A+m+1, *eR = A+r+1, *eM;
    long long cnt = 0, subans = 0;
    while(L != eL && R != eR) {
        if(*L <= *R)
            *M = *L, subans += cnt, L++, M++;
        else
            *M = *R, cnt++, R++, M++;
    }
    while(L != eL)    *M = *L, subans += cnt, L++, M++;
    while(R != eR)    *M = *R, R++, M++;
    eM = M;
    for(M = X, L = A+l; M != eM; M++, L++)
        *L = *M;
    return subans;
}
void solve(int *A, int n) {
    int i, j;
    long long ans = 0;
    for(i = 1; i < n; i <<= 1) {
        for(j = 0; j < n; j += i) {
            if(j+i-1 < n)
                ans += merge(j, j+i/2-1, j+i-1);
            else
                ans += merge(j, j+i/2-1, n-1);
        }
    }
    ans += merge(0, i/2-1, n-1);
    printf("%lld\n", ans);
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
    int n, i;
    while(ReadInt(&n)) {
        int *p = A;
        for(i = 0; i < n; i++)
            //scanf("%d", &A[i]);
            ReadInt(p), p++;
        solve(A, n);
    }
    return 0;
}
