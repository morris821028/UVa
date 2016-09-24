class Solution {
public:
    int mySqrt(int x) {
        if (x == 0)
            return 0;
        if (x == 1)
            return 1;
        double ret = x/2.f;
        for (int i = 0; i < 32; i++) {
            ret = ret / 2.f + x / (2.f * ret);
        }
        return ret;
    }
};
