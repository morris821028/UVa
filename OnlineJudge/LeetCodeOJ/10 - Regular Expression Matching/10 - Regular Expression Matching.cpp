#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <sstream>
using namespace std;

class Solution {
public:
#define MAXN 128
	int dp[MAXN][MAXN];
	int dfs(string &s, string &p, int i, int j) {
		if (dp[i][j] != -1)		return dp[i][j];
		if (i == s.length() && j == p.length())
			return 1;
		int f = 0;
		if (i < s.length() && j < p.length() && (s[i] == p[j] || p[j] == '.')) {
			f |= dfs(s, p, i+1, j+1);
		}
		if (i < s.length() && j < p.length() && p[j] == '*') {
			if (j-1 >= 0 && (p[j-1] == '.' || p[j-1] == s[i]))
				f |= dfs(s, p, i+1, j);
		}
		if (j+1 < p.length() && p[j+1] == '*')
			f |= dfs(s, p, i, j+2);
		if (j < p.length() && p[j] == '*')
			f |= dfs(s, p, i, j+1);
		return dp[i][j] = f;
	}
    bool isMatch(string s, string p) {
        memset(dp, -1, sizeof(dp));
        int v = dfs(s, p, 0, 0);
        return v;
    }
};

int main() {
	Solution s;
	s.isMatch("aa","a");
	s.isMatch("aa","aa");
	s.isMatch("aaa","aa");
	s.isMatch("aa", "a*");
	s.isMatch("aa", ".*");
	s.isMatch("ab", ".*");
	s.isMatch("aab", "c*a*b");
	s.isMatch("aab", "a*b");
	return 0;
}
