#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int MAXN = 131072;

int g[16][16];
int dp[1<<17][16];
int main() {
    int testcase;
    int cases = 0, n;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        }
        
        int ret[16][2], A[16];
        A[0] = n/2;
        for (int i = 1; i < n; i++)
            A[i] = A[i-1]/2;
        for (int i = 0; i < n; i++)
            ret[i][0] = 0, ret[i][1] = __builtin_ffs(n)-1;
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++)
            dp[1<<i][i] = 1;
        int round[64] = {1};
        for (int i = 0; i < 5; i++)
            round[1<<i] = i;
        for (int i = 0; i < (1<<n); i++) {
            int cnt = __builtin_popcount(i);
            if (cnt != (cnt & (-cnt)))
                continue;
            if (cnt == 1)
                continue;
            for (int j = (i-1)&i; j; j = (j-1)&i) {
                if (__builtin_popcount(j) != cnt/2)
                    continue;
                for (int p = 0; p < n; p++) {
                    if (dp[j][p])
                    for (int q = 0; q < n; q++) {
                        if (dp[i^j][q]) {
                            if (g[p][q]) {
                                dp[i][p] = 1;
//                                printf("%d %d %d\n", cnt, p, q);
                                ret[p][0] = max(ret[p][0], round[cnt]);
                                ret[q][1] = min(ret[q][1], round[cnt]-1);
                            } else {
//                                printf("%d %d %d\n", cnt, q, p);
                                dp[i][q] = 1;
                                ret[p][1] = min(ret[p][1], round[cnt]-1);
                                ret[q][0] = max(ret[q][0], round[cnt]);
                            }
                        }
                    }
                }
            }
        }
//        for (int i = 0; i < n; i++) {
//            printf("[%d] %d\n", i, dp[(1<<n)-1][i]);
//        }
        printf("Case #%d:\n", ++cases);
        
        int rank[16];
        for (int i = 0, sum = 0; i < n; i++) {
            sum += n>>(i+1);
            if ((1<<i) == n)
                rank[i] = 1;
            else
                rank[i] = n - sum + 1;
        }
        for (int i = 0; i < n; i++) {
            int a = ret[i][0];
            int b = ret[i][1];
//            if (ret[i][1] != n) a = max(a, ret[i][1]);
//            if (ret[i][0] != -1) b = min(b, ret[i][0]);
            printf("%d %d\n", rank[a], rank[b]);
        }
    }
    return 0;
}