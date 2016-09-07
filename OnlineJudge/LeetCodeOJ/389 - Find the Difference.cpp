class Solution {
public:
    char findTheDifference(string s, string t) {
        int mm[128] = {};
        for (int i = 0; i < s.length(); i++)
            mm[s[i]]++;
        for (int i = 0; i < t.length(); i++)
            mm[t[i]]--;
        for (int i = 'a'; i <= 'z'; i++) {
            if (mm[i])
                return i;
        }
        return '!';
    }
};
