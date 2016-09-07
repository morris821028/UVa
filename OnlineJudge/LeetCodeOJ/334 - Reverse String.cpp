class Solution {
public:
    string reverseString(string s) {
        for (int i = 0, j = s.length()-1; i < j; i++, j--)
            swap(s[i], s[j]);
        return s;
    }
};
