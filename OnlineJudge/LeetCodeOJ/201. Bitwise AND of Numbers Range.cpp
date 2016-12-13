class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int s = 0;
        while (m != n)
            m >>= 1, n >>= 1, s++;
        return m<<s;
    }
};
