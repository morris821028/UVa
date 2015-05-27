#include <stdio.h>
#include <string.h>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
 		stack< pair<char, int> > stk;
 		int ret = 0, mlen = 0;
 		for (int i = 0; i < s.length(); i++) {
 			if (s[i] == '(') {
 				stk.push(make_pair(s[i], i));
 			} else {
 				if (stk.empty() || stk.top().first == ')') {
 					stk.push(make_pair(s[i], i));
 				} else {
 					stk.pop();
 					if (stk.empty())
 						mlen = i+1;
 					else
 						mlen = i-stk.top().second;
 					ret = max(ret, mlen);
 				}
 			}
 		}
        return ret;
    }
};
Solution s;
int main() {
	int r = s.longestValidParentheses(")()())");
	printf("%d\n", r);
	return 0;
}
