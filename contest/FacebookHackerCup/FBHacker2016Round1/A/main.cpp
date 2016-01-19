#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 131072;
const int LMAX = 0x3f3f3f3f;
int dp[MAXN];
int main() {
    int testcase, n, x;
    int cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        vector<int> A;
        for (int i = 0; i < n; i++)
            scanf("%d", &x), A.push_back(x);
        
        for (int i = 0; i <= n; i++)
            dp[i] = LMAX;
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<int> S;
            for (int j = 0; j < 4 && i+j < n; j++) {
                if (j && A[i+j] <= A[i+j-1])
                    break;
                S.push_back(A[i+j]);
                int inner = 0;
                for (int k = 0; k < j; k++) {
                    int diff = S[k+1] - S[k];
                    inner += max(diff / 10 + (diff % 10 != 0) - 1, 0);
                }
//                printf("[%2d,%2d] %d %d\n", i, j, inner, (int) S.size());
                if (inner + S.size() <= 4) {
//                    printf("update %d = %d from %d\n", i+j+1, dp[i] + 4 - (int) S.size(), dp[i]);
                    dp[i+j+1] = min(dp[i+j+1], dp[i] + 4 - (int) S.size());
                }
            }
        }
        printf("Case #%d: %d\n", ++cases, dp[n]);
    }
    return 0;
}