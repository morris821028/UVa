class Solution {
public:
    int64_t str2int(string s) {
        stringstream sin(s);
        int64_t x;
        sin >> x;
        return x;
    }
    string int2str(int64_t x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    int64_t test(string part, string s) {
        int64_t o = str2int(s), mn = -1;
        int64_t ret = -1;
        for (int i = -1; i <= 1; i++) {
            string x = int2str(str2int(part)+i);
            string rs = x;
            reverse(rs.begin(), rs.end());
            int64_t cand[2] = {str2int(x + rs), str2int(x + rs.substr(1))};
            sort(cand, cand+2);
            for (int j = 0; j < 2; j++) {
                if (o == cand[j])
                    continue;
                if (mn == -1 || llabs(o - cand[j]) < mn) {
                    mn = llabs(o - cand[j]), ret = cand[j];
                } 
            }
        }
        return ret;
    }
    string nearestPalindromic(string s) {
        if (s.length() == 1)
            return int2str(str2int(s)-1);
        int n = s.length();
        int m = n/2;
        int64_t cand[3] = { test(s.substr(0, m+1), s),
                            test(s.substr(0, m), s),
                            test(s.substr(0, m) + "0", s)};
        int64_t o = str2int(s), mn = -1, ret;
        sort(cand, cand+3);
        for (int i = 0; i < 3; i++) {
            if (o == cand[i] || cand[i] == -1)
                continue;
            if (mn == -1 || llabs(o - cand[i]) < mn) {
                mn = llabs(o - cand[i]), ret = cand[i];
            }
        }
        return int2str(ret);
    }
};
/*
"11"
"1001"
"999"
"123124"
"230"
*/
