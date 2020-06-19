class Solution {
public:
    int numSquares(int n) {
        while (n % 4 == 0)
            n >>= 2;
        
        if (n % 8 == 7)
            return 4;
        
        int sq = sqrt(n);
        if (sq * sq == n)
            return 1;
        for (int i = 1; i <= sq; i++) {
            int j = sqrt(n - i*i);
            if (i * i + j * j == n)
                return 2;
        }
        return 3;
    }
};
