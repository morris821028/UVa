class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        map<string, vector<string>>  R;
        for (auto s: paths) {
            stringstream sin(s);
            string prefix, token;
            sin >> prefix;
            while (sin >> token) {
                int pos = token.find('(');
                string file = token.substr(0, pos);
                string cont = token.substr(pos+1, token.length()-pos-2);
                R[cont].push_back(prefix + "/" + file);
            }
        }
        vector<vector<string>> ret;
        for (auto e: R) {
            if (e.second.size() != 1)
                ret.push_back(e.second);
        }
        return ret;
    }
};
