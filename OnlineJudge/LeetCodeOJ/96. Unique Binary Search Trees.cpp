class Solution {
public:
    int numTrees(int n) {
        int dp[105] = {1, 1};
        for (int i = 2; i <= n; i++) {
            int v = 0;
            for (int j = 0; j < i; j++)
                v += dp[j] * dp[i-j-1];
            dp[i] = v;
        }
        return dp[n];
    }
};
