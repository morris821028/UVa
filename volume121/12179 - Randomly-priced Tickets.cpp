#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int g[128][128];
double dp[128][10005];
int main() {
    int testcase, cases = 0;
    int N, R, Q, x, y, r;
    char s[128];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &R);
        for (int i = 0; i < N; i++) {
            scanf("%s", s);
            for (int j = 0; j < N; j++) {
                g[i][j] = s[j] == 'Y' ? 1 : 0x3f3f3f3f;
            }
        }
        // floyd
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
        // probability
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1; // [[path length][cost]
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < 10005; j++) {
                if (dp[i][j] == 0)
                    continue;
                for (int k = 1; k <= R && j + k < 10005; k++) {
                    dp[i+1][j+k] += dp[i][j] / R;
                }
            }
        }
        // query
        printf("Case %d\n", ++cases);
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d %d %d", &x, &y, &r);
            x--, y--;
            int dist = g[x][y];
            double p = 0;
            if (dist == 0x3f3f3f3f) {
                p = 0;
            } else {
                for (int i = r; i >= 0; i--) {
                    p += dp[dist][i];
                }
            }
            printf("%.6lf\n", p);
        }
        puts("");
    }
    return 0;
}

/*
 2
 3 4
 NYY
 YNY
 YYN
 1
 1 3 1
 4 7
 NYNN
 YNYN
 NYNY
 NNYN
 2
 1 3 10
 1 4 10
 */