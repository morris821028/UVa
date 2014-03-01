#include <stdio.h>
#include <algorithm>
using namespace std;
int A[105];
int main() {
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        int dp[500][2] = {};
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        for(i = 0; i < n; i++) {
            dp[i+1][0] = max(dp[i+1][0], dp[i][0]+A[i]);
            dp[i+1][0] = max(dp[i+1][0], dp[i][1]);
            dp[i+1][1] = max(dp[i+1][0], dp[i][0]+2*A[i]);
        }
        printf("%d\n", max(dp[n][0], dp[n][1]));
    }
    return 0;
}
