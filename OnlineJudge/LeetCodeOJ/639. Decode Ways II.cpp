class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        vector<long long> dp(n+1, 0);
        dp[0] = 1;
        const long long MOD = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            if (dp[i] == 0)
                continue;
            if (i < n && s[i] == '*') {
                dp[i+1] += dp[i]*9;
                dp[i+1] %= MOD;
            }
            else if (i < n && s[i] != '*') {
                if (s[i] > '0')
                    dp[i+1] += dp[i], dp[i+1] %= MOD;
            }
            
            if (i+1 < n && s[i] == '*' && s[i+1] == '*') {
                dp[i+2] += dp[i]*15;
                dp[i+2] %= MOD;
            }
            else if (i+1 < n && s[i] != '*' && s[i+1] == '*') {
                for (int j = 1; j < 10; j++) {
                    int x = (s[i]-'0')*10 + j;
                    if (x >= 10 && x <= 26) {
                        dp[i+2] += dp[i];
                        dp[i+2] %= MOD;
                    }
                }
            }
            else if (i+1 < n && s[i] == '*' && s[i+1] != '*') {
                for (int j = 1; j < 10; j++) {
                    int x = (s[i+1]-'0') + j*10;
                    if (x >= 1 && x <= 26) {
                        dp[i+2] += dp[i];
                        dp[i+2] %= MOD;
                    }
                }
            }
            else if (i+1 < n && s[i] != '*' && s[i+1] != '*') {
                int x = (s[i+1]-'0') + (s[i]-'0')*10;
                if (x >= 10 && x <= 26) {
                    dp[i+2] += dp[i];
                    dp[i+2] %= MOD;
                }
            }
        }
        return dp[n] % MOD;
    }
};
