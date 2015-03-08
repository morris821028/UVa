#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
// binary search + DP
#define eps 1e-8
#define MAXN 5005
#define MAXM 55
#define INF 0x3f3f3f3f
int dp[MAXN][MAXM], xlen, ylen;
char x[MAXN], y[MAXM];
int test(int k) {
    for (int i = 0; i <= xlen; i++)
        for (int j = 0; j <= ylen; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;
    for (int i = 0; i <= xlen; i++) {
        if (dp[i][ylen] <= k)
            dp[i][0] = 0;
        for (int j = 0; j <= ylen; j++) {
            if (dp[i][j] > k)
                continue;
            if (x[i] == y[j])
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
            dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);       // delete x[i]
            dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+1);   // change x[i], y[j]
            dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);       // delete y[j]
        }
    }
    return dp[xlen][ylen] <= k;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s %s", y, x);
        xlen = (int) strlen(x), ylen = (int) strlen(y);
        int l = 0, r = ylen, mid = 0, ret = 0;
        while (l <= r) {
            mid = (l + r)/2;
            if (test(mid))
                r = mid - 1, ret = mid;
            else
                l = mid + 1;
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*

*/