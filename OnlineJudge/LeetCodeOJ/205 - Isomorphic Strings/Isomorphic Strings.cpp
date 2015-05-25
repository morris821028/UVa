class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int R1[256] = {}, R2[256] = {};
        for (int i = 0; i < s.length(); i++)
            R1[s[i]] = t[i], R2[t[i]] = s[i];
        for (int i = 0; i < s.length(); i++) {
            if (R1[s[i]] != t[i] || R2[t[i]] != s[i])
                return false;
        }
        return true;
    }
};