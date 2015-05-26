class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret = "";
        if (strs.size() == 0)
            return ret;
            
        for (int it = 0; ; it++) {
            int same = 1;
            for (int i = 0; i < strs.size() && same; i++) {
                if (it >= strs[i].length())
                    same = 0;
                same &= strs[0][it] == strs[i][it];
            }
            if (!same)  break;
            ret += strs[0][it];
        }
        return ret;
    }
};
