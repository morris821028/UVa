class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int dp[32] = {1};
        dp[1] = 9;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i-1] * (10 - i + 1);
        int ret = 0;
        for (int i = 0; i <= n; i++)
            ret += dp[i];
        return ret;
    }
};
