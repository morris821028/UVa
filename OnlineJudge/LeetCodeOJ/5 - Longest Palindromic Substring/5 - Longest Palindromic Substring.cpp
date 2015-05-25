#include <stdio.h>
#include <string.h> 
#include <iostream>
using namespace std;


class Solution {
public:
    string longestPalindrome(string s) { // manacher's algorithm
        const int MAXL = 2048;
        char T[MAXL];
        int dp[MAXL];
        int n = s.length(), m = 2 * n + 1;
        int mx = 0, idx = 0;
        
    	T[0] = '$', T[m] = '#', T[m + 1] = '\0';
    	
    	for (int i = 0; i < n; i++)
        	T[i * 2 + 1] = '#', T[i * 2 + 2] = s[i];
        	
        for (int i = 1; i < m; i++) {
            if (mx > i) {
            	dp[i] = min(dp[2*idx-i], mx-i);
            } else {
                dp[i] = 1;
            }
    		for(; T[i-dp[i]] == T[i+dp[i]]; dp[i]++);
    		
            if(dp[i] + i > mx)		mx = dp[i] + i, idx = i;
        }
        
        int retLen = 0, retMid = -1;
        string ret = "";
        for (int i = 1, j = 0; i < m; i ++, j++) {
        	if (dp[i] > retLen) {
        		retLen = dp[i], retMid = i;
        	}
        }
        if (T[retMid] == '#') {
        	for (int i = 1; i < retLen; i += 2)
        		ret = T[retMid+i] + ret + T[retMid+i];
        } else {
        	ret = T[retMid];
        	for (int i = 2; i < retLen; i += 2)
        		ret = T[retMid+i] + ret + T[retMid+i];
        }
        cout << ret << endl;
        return ret;
    }
};

int main() {
	Solution s;
	s.longestPalindrome("abccb");
	s.longestPalindrome("abad");
	return 0;
}
