#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define MAXN 105
#define INF 0x3f3f3f3f
int N, p[MAXN], e[MAXN], cases = 0;
int dp[MAXN][MAXN][MAXN][2], used[MAXN][MAXN][MAXN][2];
// [left][right][leave visit][on left/right]
void update(int l, int r, int k, int val, int pp) {
    if (l-1 >= 0) {
        if (used[l-1][r][k-1][0] != cases) {
            used[l-1][r][k-1][0] = cases;
            dp[l-1][r][k-1][0] = -INF;
        }
        dp[l-1][r][k-1][0] = max(dp[l-1][r][k-1][0], val+e[l-1]-abs(pp-p[l-1])*k);
        
        if (used[l-1][r][k][0] != cases) {
            used[l-1][r][k][0] = cases; // passing
            dp[l-1][r][k][0] = -INF;
        }
        dp[l-1][r][k][0] = max(dp[l-1][r][k][0], val-abs(pp-p[l-1])*(k));
    }
    if (r+1 < N) {
        if (used[l][r+1][k-1][1] != cases) {
            used[l][r+1][k-1][1] = cases;
            dp[l][r+1][k-1][1] = -INF;
        }
        dp[l][r+1][k-1][1] = max(dp[l][r+1][k-1][1], val+e[r+1]-abs(pp-p[r+1])*k);
        
        if (used[l][r+1][k][1] != cases) {
            used[l][r+1][k][1] = cases; // passing
            dp[l][r+1][k][1] = -INF;
        }
        dp[l][r+1][k][1] = max(dp[l][r+1][k][1], val-abs(pp-p[r+1])*(k));
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &p[i]);
        for (int i = 0; i < N; i++)
            scanf("%d", &e[i]);
        cases++;
        int ret = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 1; j <= N; j++) {
                dp[i][i][j-1][0] = e[i] - abs(p[i] - 0) * j;
                used[i][i][j-1][0] = cases;
            }
        }
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < N; j++) {
                int l = j, r = j+i;
                if (r > N)  break;
                if (used[l][r][0][0] == cases)
                    ret = max(ret, dp[l][r][0][0]);
                if (used[l][r][0][1] == cases)
                    ret = max(ret, dp[l][r][0][1]);
                for (int k = 1; k <= N; k++) {
                    if (used[l][r][k][0] == cases) {
                        int val = dp[l][r][k][0];
                        update(l, r, k, val, p[l]);
                    }
                    if (used[l][r][k][1] == cases) {
                        int val = dp[l][r][k][1];
                        update(l, r, k, val, p[r]);
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
*/