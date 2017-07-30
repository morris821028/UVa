class Solution {
public:
    int kInversePairs(int n, int k) {
        const int MOD = 1e9 + 7;
        int dp[2][1024] = {};
        int p = 0, q = 1;
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int j = 0; j <= k; j++) {
                sum = sum + dp[p][j];
                if (sum >= MOD) sum -= MOD;
                if (j-i >= 0)
                    sum -= dp[p][j-i];
                if (sum < 0)    sum += MOD;
                dp[q][j] = sum;
            }
            p = 1-p, q = 1-q;
        }
        return dp[p][k];
    }
};
