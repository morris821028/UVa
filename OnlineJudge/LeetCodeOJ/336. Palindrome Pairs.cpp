class Solution {
public:
    bool isPal(const string &x) {
        int n = x.length();
        for (int i = 0, j = n-1; i < j; i++, j--) {
            if (x[i] != x[j])
                return false;
        }
        return true;
    }
    vector< vector<int> > palindromePairs(vector<string>& W) {
        unordered_map<string, int> R;
        for (int i = 0; i < W.size(); i++) {
            string s = W[i];
            reverse(s.begin(), s.end());
            R[s] = i;
        }
        
        vector<vector<int> > ret;
        for (int i = 0; i < W.size(); i++) {
            string s = W[i];
            int n = s.length();
            for (int j = 0; j < n; j++) {
                string l = s.substr(0, j);
                string r = s.substr(j);
                unordered_map<string, int>::iterator it;
                it = R.find(l);
                if (it != R.end() && it->second != i && isPal(r)) {
                    ret.push_back({i, it->second});
                    if (l.length() == 0)
                        ret.push_back({it->second, i});
                }
                it = R.find(r);
                if (it != R.end() && it->second != i && isPal(l)) {
                    ret.push_back({it->second, i});
                }
            }
        }
        return ret;
    }
};
