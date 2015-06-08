#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
    	int n = (int) s1.length();
    	int m = (int) s2.length();
        vector< vector<int> > dp(n+1, vector<int>(m+1, 0));
        
        if (n+m != s3.length())
        	return false;
        	
        dp[0][0] = 1;
        for (int i = 0; i <= n; i++) {
        	for (int j = 0; j <= m; j++) {
        		if (i == n && j == m)
        			continue;
        		if (s3[i+j] == s1[i])
        			dp[i+1][j] |= dp[i][j];
        		if (s3[i+j] == s2[j])
        			dp[i][j+1] |= dp[i][j];
        	}
        }
        return dp[n][m];
    }
};

int main() {
	Solution s;
	printf("%d\n", s.isInterleave("aabcc", "dbbca", "aadbbcbcac"));
	return 0;
}
