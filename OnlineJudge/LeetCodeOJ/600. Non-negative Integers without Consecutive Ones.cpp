class Solution {
public:
    int findIntegers(int num) {
        int dp[32][2][2] = {};
        // [digits][tail 0/1][has been less than]
        dp[31][0][0] = 1;
        for (int i = 30; i >= 0; i--) {
            int t = (num>>i)&1;
            if (t == 1) {
                dp[i][1][0] += dp[i+1][0][0];
                dp[i][0][1] += dp[i+1][0][0] + dp[i+1][1][0];
            } else {
                dp[i][0][0] += dp[i+1][0][0] + dp[i+1][1][0];
            }
            dp[i][0][1] += dp[i+1][0][1] + dp[i+1][1][1];
            dp[i][1][1] += dp[i+1][0][1];
        }
        
        int ret = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                ret += dp[0][i][j];
        }
        return ret;
    }
};
