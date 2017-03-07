class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if (z == 0)
            return true;
        if (x == 0 && y == 0)
            return false;
        return z <= x + y && z % __gcd(x, y) == 0;
    }
};
