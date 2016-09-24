class Solution {
public:
    string addBinary(string a, string b) {
        int n = a.length(), m = b.length();
        int cn = max(n,m)+1;
        vector<char> ret(cn, 0);
        for (int i = n-1, j = 0; i >= 0; i--, j++)
            ret[j] += a[i]-'0';
        for (int i = m-1, j = 0; i >= 0; i--, j++)
            ret[j] += b[i]-'0';
        for (int i = 0; i < cn-1; i++) {
            if (ret[i] >= 2)
                ret[i+1] += ret[i]/2, ret[i] &= 1;
        }
        int end = cn-1;
        while (end > 0 && ret[end] == 0)
            end--;
        for (int i = 0; i <= end; i++)
            ret[i] += '0';
        reverse(ret.begin(), ret.begin()+end+1);
        return string(ret.begin(), ret.begin()+end+1);
    }
};
