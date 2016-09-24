class Solution {
public:
    int minPathSum(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();
        vector<vector<int>> dp = g;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > 0 && j > 0)
                    dp[i][j] += min(dp[i-1][j], dp[i][j-1]);
                else if (i > 0)
                    dp[i][j] += dp[i-1][j];
                else if (j > 0)
                    dp[i][j] += dp[i][j-1];
                    
            }
        }
        return dp[n-1][m-1];
    }
};
