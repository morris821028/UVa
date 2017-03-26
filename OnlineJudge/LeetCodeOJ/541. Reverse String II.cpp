class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.length();
        for (int i = 0; i < n; i += 2*k) {
            int l = i, r = min(i+k, n);
            for (int p = l, q = r-1; p < q; p++, q--)
                swap(s[p], s[q]);
        }
        return s;
    }
};
