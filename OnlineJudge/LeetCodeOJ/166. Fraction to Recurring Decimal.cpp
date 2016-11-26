class Solution {
public:
    string int2str(long long x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    string fractionToDecimal(long long A, long long B) {
        string ret = "";
        if (B < 0)
            B = -B, A = -A;
        if (A < 0)
            ret += "-", A = -A;
        ret += int2str(A/B), A %= B;
        if (A == 0)
            return ret;
        ret += ".";
        map<int, int> R;
        for (int x = ret.length(); A; x++) {
            if (R.count(A)) {
                ret.insert(R[A], "(");
                ret += ")";
                return ret;
            } else {
                R[A] = x;
            }
            ret += int2str(A * 10 / B);
            A = (A * 10)%B;
        }
        return ret;
    }
};
