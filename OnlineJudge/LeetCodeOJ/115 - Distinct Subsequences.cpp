#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = (int) s.length();
    	int m = (int) t.length();
        vector< vector<int> > dp(n+1, vector<int>(m+1, 0));
        
        for (int i = 0; i <= n; i++)
        	dp[i][0] = 1;
        for (int i = 1; i <= n; i++) {
        	for (int j = 1; j <= m; j++) {
        		if (s[i-1] == t[j-1])
        			dp[i][j] += dp[i-1][j-1];
        		dp[i][j] += dp[i-1][j];
        	}
        }
        return dp[n][m];
    }
};

int main() {
	Solution s;
	printf("%d\n", s.numDistinct("rabbbit", "rabbit"));
	printf("%d\n", s.numDistinct("ccc", "c"));
	return 0;
}
