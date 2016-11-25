class Solution {
public:
    void reverse(string &s, int l, int r) {
        for (int i = l, j = r; i < j; i++, j--)
            swap(s[i], s[j]);
    }
    void reverseWords(string &s) {
        int n = s.length();
        reverse(s, 0, n-1);
        int pos = 0;
        for (int i = 0; i < n; ) {
            while (i < n && isspace(s[i]))
                i++;
            if (i == n)
                break;
            int l = i, r = i;
            while (r+1 < n && !isspace(s[r+1]))
                r++;
            reverse(s, l, r);
            if (pos)
                s[pos++] = ' ';
            for (int j = l; j <= r; j++)
                s[pos++] = s[j];
            i = r+1;
        }
        s = s.substr(0, pos);
    }
};
