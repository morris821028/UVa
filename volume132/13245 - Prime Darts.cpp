#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[5500], Pt = 0;
void sieve() {
    int i, j, k;
    SET(1);
    int n = 50000;
    P[Pt++] = 1;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

int main() {
    sieve();
    static int dp[8192] = {};
    int testcase, n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        memset(dp, 0x3f, sizeof(dp[0])*(m+1));
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            int p = P[i];
            for (int j = p; j <= m; j++)
                dp[j] = min(dp[j], dp[j-p]+1);
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}
/*
 6
 1 200
 5 15
 5 34
 6 34
 7 4
 20 1000
*/

