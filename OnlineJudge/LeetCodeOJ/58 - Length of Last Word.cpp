class Solution {
public:
    int lengthOfLastWord(string s) {
        int ret = 0;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            if (!isspace(s[i])) {
                int cnt = 0;
                while (i < n && !isspace(s[i])) {
                    cnt++;
                    i++;
                }
                ret = cnt;
            }
        }
        return ret;
    }
};
