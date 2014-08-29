#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;

int dp[2][105][1<<8][8];
// [i-th book][pick up j book][leave kind book on shelf][last book height on shelf]
int main() {
    int n, m, A[128], cases = 0;
    while (scanf("%d %d", &n, &m) == 2 && n + m) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &A[i]);
            A[i] -= 25;
        }
        
        memset(dp, 63, sizeof(dp));
        int p = 0, q = 1, kind = 0;
        for (int i = 1; i <= n; i++) {
            memset(dp[q], 63, sizeof(dp[q]));
            int h = A[i];
            dp[q][i-1][1<<h][h] = 1;
            for (int j = min(m, i-1); j >= 0; j--) {
                for (int k = kind; k > 0; k = (k-1)&kind) { // subset
                    for (int l = 0; (1<<l) <= k; l++) {
                        if (h == l) { // same, greedy - put
                            dp[q][j][k][l] = min(dp[q][j][k][l], dp[p][j][k][l]);
                        } else {
                            // put
                            dp[q][j][k|(1<<h)][h] = min(dp[q][j][k|(1<<h)][h], dp[p][j][k][l] + 1);
                            // pick
                            dp[q][j+1][k][l] = min(dp[q][j+1][k][l], dp[p][j][k][l]);
                        }
                    }
                }
            }
            swap(p, q), kind |= (1<<h);
        }
        
        int ret = 0x3f3f3f3f;
        for (int i = 0; i <= m; i++) {
            for (int j = kind; j > 0; j = (j-1)&kind) {
                for (int k = 0; (1<<k) <= j; k++) {
                    ret = min(ret, dp[p][i][j][k] + __builtin_popcount(kind^j));
                }
            }
        }
        printf("Case %d: %d\n\n", ++cases, ret);
    }
    return 0;
}
/*
 5 2
 25 25 32 32 25
 5 1
 25 26 25 26 25
 0 0
 */