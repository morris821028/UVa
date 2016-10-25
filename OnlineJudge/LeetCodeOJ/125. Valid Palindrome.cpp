class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.length()-1;
        while (l < r) {
            while (l < r && !isalpha(s[l]) && !isdigit(s[l])) l++;
            while (l < r && !isalpha(s[r]) && !isdigit(s[r])) r--;
            if (l < r && tolower(s[l]) != tolower(s[r]))
                return false;
            l++, r--;
        }
        return true;
    }
};
