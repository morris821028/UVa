#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>

using namespace std;

int dp[128][3024], dp_path[128][3024];
int main() {
    const int w[10]={ 6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int n, m, cases = 0;
    
    while (scanf("%d %d", &n, &m) == 2 && n) {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < m; j++)
                dp[i][j] = -1, dp_path[i][j] = 0;
        dp[0][0] = 0;
        int mxlen = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                if (dp[i][j] == -1)
                    continue;
                for (int k = 0; k < 10; k++) {
                    int p = i + w[k], q = (j*10 + k)%m;
                    dp[p][q] = max(dp[p][q], dp[i][j]+1);
                }
            }
            mxlen = max(mxlen, dp[i][0]);
        }
        
//        printf("mxlen %d\n", mxlen);
        for (int i = n; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                if (dp[i][j] == -1)
                    continue;
                for (int k = 0; k < 10; k++) {
                    int p = i + w[k], q = (j*10 + k)%m;
                    if (p > n)  continue;
                    if (dp[p][q] == dp[i][j] + 1)
                        dp_path[i][j] |= dp_path[p][q];
                }
            }
            if (dp[i][0] == mxlen)
                dp_path[i][0] = 1;
        }
        
        printf("Case %d: ", ++cases);
        for (int i = 0, p = 0, q = 0; i < mxlen; i++) {
            for (int k = 9; k >= 0; k--) {
                int pp = p + w[k], qq = (q*10 + k)%m;
                if (dp_path[pp][qq] && dp[pp][qq] == dp[p][q]+1) {
                    p = pp, q = qq;
                    printf("%d", k);
                    break;
                }
            }
        }
        if (mxlen == 0)
            printf("-1");
        puts("");
    }
    return 0;
}


/*
 6 3
 5 6
 0
 */