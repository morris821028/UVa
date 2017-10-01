class Solution {
public:
    string convertToBase7(int n) {
        if (n == 0)
            return "0";
        string sign = n < 0 ? "-" : "", ret = "";
        n = abs(n);
        while (n) {
            ret = (char) (n%7+'0') + ret;
            n = n/7;
        }
        return sign + ret;
    }
};
