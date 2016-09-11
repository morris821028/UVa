class Solution {
public:
	void dfs2(string s, set<string> &S) {
        for (int i = s.length()-1, r = 0; i >= 0; i--) {
        	if (s[i] == '(')	r--;
        	if (s[i] == ')')	r++;
        	if (r >= 0)	continue;
        	// remove '('
        	for (int j = i; j < s.length(); j++) {
        		if (s[j] == '(' && (j == s.length()-1 || s[j+1] != '(')) {
        			string tmp = s;
        			tmp.erase(j, 1);
        			dfs2(tmp, S);
				}
			}
        	return ;
		}
		S.insert(s);
    }
    void dfs1(string s, set<string> &S) {
        for (int i = 0, l = 0; i < s.length(); i++) {
        	if (s[i] == '(')	l++;
        	if (s[i] == ')')	l--;
        	if (l >= 0)	continue;
        	// remove ')'
        	for (int j = 0; j <= i; j++) {
        		if (s[j] == ')' && (j == 0 || s[j-1] != ')')) {
        			string tmp = s;
        			tmp.erase(j, 1);
        			dfs1(tmp, S);
				}
			}
        	return ;
		}
		dfs2(s, S);
    }
    vector<string> removeInvalidParentheses(string s) {
        set<string> S;
        vector<string> ret;
        dfs1(s, S);
        for (auto &t : S)
            ret.push_back(t);
        return ret;
    }
};
