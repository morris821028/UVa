#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int A[32767];
int cg[5][5] = {
    {0, 2, 2, 2, 2},
    {INF, 1, 3, 4, 3},
    {INF, 3, 1, 3, 4},
    {INF, 4, 3, 1, 3},
    {INF, 3, 4, 3, 1}
};
int main() {
    while (scanf("%d", &A[0]) == 1 && A[0]) {
        int n = 1;
        for (; scanf("%d", &A[n]) && A[n]; n++);
        int dp[2][5][5]; // [][left][right]
        memset(dp, 0x3f, sizeof(dp));
        int p = 0, q = 1;
        dp[p][0][0] = 0;
        for (int i = 0; i < n; i++) {
            p = !p, q = !q;
            memset(dp[p], 0x3f, sizeof(dp[p]));
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    int l = A[i];
                    if (j != l) {
                        dp[p][j][l] = min(dp[p][j][l], dp[q][j][k] + cg[k][l]);
                    }
                    if (k != l) {
                        dp[p][l][k] = min(dp[p][l][k], dp[q][j][k] + cg[j][l]);
                    }
                    if (j == l || k == l) {
                        dp[p][j][k] = min(dp[p][j][k], dp[q][j][k] + 1);
                    }
                }
            }
        }
        
        int ret = INF;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                ret = min(ret, dp[p][i][j]);
            }
        }
        
        printf("%d\n", ret);
    }
    return 0;
}
/*
 1 2 2 4 0
 1 2 3 4 1 2 3 3 4 2 0
 0
 */
