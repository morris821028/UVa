#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void dfs(int idx, int left, string s, vector<string> &ret) {
		if (idx == 0 && left == 0) {
			ret.push_back(s);
			return ;
		}
		if (idx > 0)
			dfs(idx-1, left+1, s + "(", ret);
		if (left > 0)
			dfs(idx, left-1, s + ")", ret);
	}
    vector<string> generateParenthesis(int n) {
    	vector<string> ret;
    	dfs(n, 0, "", ret);
        return ret;
    }
};

int main() {
	Solution s;
	
	s.generateParenthesis(3);
	return 0;
}
