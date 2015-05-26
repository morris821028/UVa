#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        string SMS[] = {"", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		vector<string> ret;
		if (digits.length() > 0)
			dfs(0, digits, "", SMS, ret);
		return ret;
    }
    void dfs(int idx, string &digits, string s, string SMS[], vector<string> &ret) {
    	if (idx == digits.length()) {
    		ret.push_back(s);
    		return;
    	}
    	for (int i = 0; i < SMS[digits[idx]-'0'].length(); i++)
    		dfs(idx+1, digits, s + SMS[digits[idx]-'0'][i], SMS, ret);
    }
};

int main() {
	Solution s;
	vector<string> r = s.letterCombinations("23");
	for (int i = 0; i < r.size(); i++)
		cout << r[i] << endl;
	return 0;
}
