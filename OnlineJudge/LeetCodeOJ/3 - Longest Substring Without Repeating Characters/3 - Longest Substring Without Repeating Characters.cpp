class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int mark[256] = {};
        memset(mark, -1, sizeof(mark));
        
        int ret = 0, begin = 0;
        for (int i = 0; i < s.length(); i++) {
            if (mark[s[i]] >= 0)
                begin = max(begin, mark[s[i]]+1);
            mark[s[i]] = i;
            ret = max(ret, i - begin + 1);
        }
        return ret;
    }
};
