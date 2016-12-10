class Solution {
public:
    string convertToTitle(int n) {
        n--;
        int d = 1;
        for (long long i = 26; n >= i; i *= 26)
            n -= i, d++;
        string ret = "";
        for (int i = 0; i < d; i++)
            ret = (char) (n%26 + 'A') + ret, n /= 26;
        return ret;
    }
};
