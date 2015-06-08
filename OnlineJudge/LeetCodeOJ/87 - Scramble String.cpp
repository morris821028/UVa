#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length())
        	return false;
        string v1(s1), v2(s2);
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        if (v1 != v2)
        	return false;
        
        int n = (int) s1.length();
        vector< vector< vector<int> > > dp(n+1, vector< vector<int> >(n, vector<int>(n, 0)));
        
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < n; j++)
        		dp[1][i][j] = s1[i] == s2[j];
        for (int k = 2; k <= n; k++) {
        	for (int i = 0; i+k <= n; i++) {
        		for (int j = 0; j+k <= n; j++) {
        			int &val = dp[k][i][j]; // 
        			for (int p = 1; p < k && !val; p++) {
        				val |= dp[p][i][j] && dp[k-p][i+p][j+p];
        				val |= dp[p][i][j+k-p] && dp[k-p][i+p][j];
        			}
        		}
        	}
        }
        return dp[n][0][0];
    }
};

int main() {
	Solution s;
	printf("%d\n", s.isScramble("rgtae", "great"));
	printf("%d\n", s.isScramble("rgeat", "great"));
	printf("%d\n", s.isScramble("ba", "ab"));
	printf("%d\n", s.isScramble("ab", "ab"));
	return 0;
}
