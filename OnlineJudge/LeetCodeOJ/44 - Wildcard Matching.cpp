#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <sstream>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
    	if (s == "" && p == "")
    		return true;
        int idx1 = 0, idx2 = 0;
        int pre1 = -1, pre2 = -1;
        while (idx1 < s.length()) {
        	if (idx2 < p.length() && (s[idx1] == p[idx2] || p[idx2] == '?')) {
        		idx1++, idx2++;
        	} else if (idx2 < p.length() && p[idx2] == '*') {
        		pre1 = idx1, pre2 = idx2;
        		idx2++;
        	} else if (pre2 != -1) {
        		idx2 = pre2 + 1;
        		pre1 = pre1 + 1;
        		idx1 = pre1;
        	} else {
        		return false;
        	}
        }
        
        while (idx2 < p.length()) {
        	if (p[idx2] != '*')
        		return false;
        	idx2++;
        }
        return true;
    }
};
Solution s;
int main() {
	printf("%d", s.isMatch("aa","a"));
	printf("%d", s.isMatch("aa","aa"));
	printf("%d", s.isMatch("aaa","aa"));
	printf("%d", s.isMatch("aa", "*"));
	printf("%d", s.isMatch("aa", "a*"));
	printf("%d", s.isMatch("aa", "?*"));
	printf("%d", s.isMatch("aab", "c*a*b"));
	return 0;
}

