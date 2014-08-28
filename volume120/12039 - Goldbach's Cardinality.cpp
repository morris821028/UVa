#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[1048576], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

long long g(int n) {
    long long ret = 0;
    int pos = (int)(upper_bound(P+1, P+Pt, n) - (P+1));
    for (int i = 1; i < Pt && P[i] < n; i++) {
//        int pos = (int)(upper_bound(P+1, P+Pt, n - P[i]) - (P+1));
        while (pos > 0 && P[i] + P[pos] > n)
            pos--;
        if (pos >= i)
            ret--;
        ret += pos;
    }
    return ret/2;
}
int main() {
    sieve();
    int L, R;
    while (scanf("%d %d", &L, &R) == 2 && L+R) {
        R = R/2 * 2;
        L = (L-1)/2 * 2;
        printf("%lld\n", g(R) - g(L));
    }
    return 0;
}

/*
 10 20
 30 40
 0 0
 */
