class Solution {
public:
    int climbStairs(int n) {
        int f1 = 1, f2 = 1;
        for (int i = 1; i < n; i++) {
            int t = f1 + f2;
            f1 = f2, f2 = t;
        }
        return f2;
    }
};
