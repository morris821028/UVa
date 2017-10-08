#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        int K, Q;
        scanf("%d %d", &K, &Q);
        
        // build table
        //  (a, b)
        //  (1, k+2) is loser, otherwise (1, ?) is winner
        //  winner (2, ?) -> (1, k+2), otherwise (2, 2+k+1+k+1) is loser
        static const int MAXN = 131072;
        static int dp[MAXN];
        memset(dp, 0, sizeof(dp));
        dp[0] = 0;
        for (int i = 1, pre = 0; i < MAXN; i++) {
            if (dp[i])
                continue;
            int lose = dp[pre]-pre + i + K + 1;
            pre = i;
            dp[i] = lose;
            if (lose >= MAXN)
                continue;
            dp[lose] = i;
        }
        
        for (int i = 0; i < Q; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (a > b)  swap(a, b);
            puts(dp[a] == b ? "LOSING" : "WINNING");
        }
        puts("");
    }
    return 0;
}

