class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 0)    return false;
        unsigned int x = num;
        unsigned int l = 0, r = 65535, mid;
        while (l <= r) {
            mid = (l + r)>>1;
            unsigned int y = mid * mid;
            if (y == x)
                return true;
            if (y < x)
                l = mid+1;
            else
                r = mid-1;
        }
        return false;
    }
};
