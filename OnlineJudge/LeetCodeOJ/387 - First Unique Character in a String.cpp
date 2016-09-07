class Solution {
public:
    int firstUniqChar(string s) {
        int ret = -1;
        int mm[128] = {};
        for (int i = s.length()-1; i >= 0; i--)
            mm[s[i]]++;
        for (int i = s.length()-1; i >= 0; i--) {
            if (mm[s[i]] == 1)
                ret = i;
        }
        return ret;
    }
};
