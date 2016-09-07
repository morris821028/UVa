class Solution {
public:
    int titleToNumber(string s) {
        int ret = 1, w = 1;
        for (int i = 1; i < s.length(); i++)
            w = w * 26, ret += w;
        for (int i = s.length()-1, t = 1; i >= 0; i--) {
            ret = ret + t * (s[i] - 'A');
            t = t * 26;
        }
        return ret;
    }
};
