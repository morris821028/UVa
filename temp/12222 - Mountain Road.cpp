#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
// DP
#define eps 1e-8
#define MAXN 256
#define INF 0x3f3f3f3f
int dp[MAXN][MAXN][2];
int main() {
    int testcase, N;
    char s[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        vector< pair<int, int> > A, B;
        for (int i = 0; i < N; i++) {
            int start, pass;
            scanf("%s %d %d", s, &start, &pass);
            if (s[0] == 'A')
                A.push_back(make_pair(start, pass));
            else
                B.push_back(make_pair(start, pass));
        }
        for (int i = 0; i <= A.size(); i++) {
            for (int j = 0; j <= B.size(); j++) {
                dp[i][j][0] = dp[i][j][1] = INF;
            }
        }
        
        dp[0][0][0] = dp[0][0][1] = 0;
        for (int i = 0; i <= A.size(); i++) {
            for (int j = 0; j <= B.size(); j++) {
                if (dp[i][j][0] != INF)
                for (int k = i, start = dp[i][j][0], end = 0; k < A.size(); k++) {
                    start = max(start, A[k].first);
                    end = max(end, start + A[k].second);
                    dp[k+1][j][1] = min(dp[k+1][j][1], end);
                    start = start + 10, end = end + 10;
                }
                if (dp[i][j][1] != INF)
                for (int k = j, start = dp[i][j][1], end = 0; k < B.size(); k++) {
                    start = max(start, B[k].first);
                    end = max(end, start + B[k].second);
                    dp[i][k+1][0] = min(dp[i][k+1][0], end);
                    start = start + 10, end = end + 10;
                }
            }
        }
        int ret = min(dp[A.size()][B.size()][0], dp[A.size()][B.size()][1]);
        printf("%d\n", ret);
    }
    return 0;
}
/*

*/