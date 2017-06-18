class Solution {
public:
    string int2string(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    int string2int(string x) {
        stringstream sin(x);
        int t;
        if (sin >> t)
            return t;
        return 0;
    }
    int smallestFactorization(int n) {
        if (n == 1)
            return 1;
        int sqn = sqrt(n);
        int cnt[10] = {};
        for (int i = 9; i >= 2; i--) {
            if (n%i == 0) {
                while (n%i == 0)
                    n /= i, cnt[i]++;
            }
        }
        if (n != 1)
            return 0;
        string ret = "";
        for (int i = 2; i <= 9; i++) {
            for (int j = 0; j < cnt[i]; j++)
                ret += (char) (i+'0');
        }
        return string2int(ret);
    }
};
