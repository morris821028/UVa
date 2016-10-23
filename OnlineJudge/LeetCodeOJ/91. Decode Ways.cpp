class Solution {
public:
    int numDecodings(string s) {
        if (s.length() == 0)
            return 0;
        int n = s.length();
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for (int i = 0; i <= n; i++) {
            if (i < n && s[i]-'0' >= 1)
                dp[i+1] += dp[i];
            if (i+1 < n && (s[i]-'0')*10+s[i+1]-'0' <= 26 && (s[i]-'0') >= 1)
                dp[i+2] += dp[i];
        }
        return dp[n];
    }
};
