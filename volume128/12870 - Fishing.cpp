#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
using namespace std;
#define MAXN 128
int dp[MAXN][MAXN][MAXN];
int dp2[MAXN][MAXN][MAXN];
int main() {
    int testcase;
    int n, m, A[128][128];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &A[i][j]);
        int nm = min(n, m);
        int lenMAX[128] = {}, lenMIN[128] = {};
        for (int i = 0; i <= nm; i++) {
            lenMAX[i] = 0;
            lenMIN[i] = -0x3f3f3f3f;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k <= nm; k++) {
                    dp[i][j][k] = 0, dp2[i][j][k] = -0x3f3f3f3f;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j][1] = max(dp[i][j][1], A[i][j]);
                dp2[i][j][1] = max(dp2[i][j][1], -A[i][j]);
                for (int k = 1; k <= nm; k++) {
                    if (i > 0) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
                        dp2[i][j][k] = max(dp2[i][j][k], dp2[i-1][j][k]);
                    }
                    if (j > 0) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k]);
                        dp2[i][j][k] = max(dp2[i][j][k], dp2[i][j-1][k]);
                    }
                    if (i > 0 && j > 0) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1] + A[i][j]);
                        dp2[i][j][k] = max(dp2[i][j][k], dp2[i-1][j-1][k-1] - A[i][j]);
                    }
//                    printf("%d %d %d %d\n", i, j, k, dp2[i][j][k]);
                }
                for (int k = 1; k <= nm; k++)
                    lenMAX[k] = max(lenMAX[k], dp[i][j][k]), lenMIN[k] = max(lenMIN[k], dp2[i][j][k]);
            }
        }
        int ret = 0;
        for (int i = 2; i <= nm; i += 2) {
            ret = max(ret, lenMAX[i/2] + lenMIN[i]);
//            printf("%d %d %d\n", i, lenMAX[i/2], lenMIN[i]);
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 9999
 4 4
 1 1 1 4
 1 3 1 1
 1 1 2 1
 1 1 1 1
 3 5
 1 1 1 1 1
 1 1 1 1 1
 1 1 1 1 1
 3 4
 0 0 1 0
 0 0 2 0
 0 1 0 0
 2 2
 0 1
 2 0
 2 3
 10 20 30
 30 4 50
 3 2
 10 20
 30 30
 4 50
 */