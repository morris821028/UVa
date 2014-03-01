#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct ele {
    int a;
    short b;
};
short mark[2000005];
ele dp[2000005], dp2[2000005];
void RadixSort(ele *A, ele *B, int n) {
    int a, x, d, C[16];
    ele *T;
    for(x = 0; x < 2; x++) {
        d = x*4;
        for(a = 0; a < 16; a++)     C[a] = 0;
        for(a = 0; a < n; a++)      C[(A[a].b>>d)&15]++;
        for(a = 1; a < 16 ; a++)    C[a] += C[a-1];
        for(a = n-1; a >= 0; a--)   B[--C[(A[a].b>>d)&15]] = A[a];
        T = A, A = B, B = T;
    }
}
bool cmp(ele a, ele b) {
    if(a.b != b.b)
        return a.b < b.b;
    return a.a < b.a;
}
void sieve() {
    int i, j;
    const int n = 2000000, sq = (int)sqrt(n);
    for(i = 2; i <= sq; i++) {
        if(mark[i] == 0) {
            for(j = i+i; j <= n; j += i)
                mark[j] = i;
        }
    }
    for(i = 2; i <= n; i++) {
        if(mark[i])
            mark[i] = mark[i/mark[i]]+1;
        else
            mark[i] = 1;
        dp[i].a = i, dp[i].b = mark[i];
    }
    dp[1].a = 1, dp[1].b = 1;
    //sort(dp+1, dp+1+n, cmp);
    RadixSort(dp+1, dp2, n);
}
inline int ReadInt(int *x) {
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
    sieve();
    int n, cases = 0;
    while(ReadInt(&n) && n)
        printf("Case %d: %d\n", ++cases, dp[n].a);
    return 0;
}
