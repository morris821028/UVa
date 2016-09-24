class Solution {
public:
    int C[128][128];
    Solution() {
        memset(C, 0, sizeof(C));
        C[0][0] = 1;
        for (int i = 1; i < 128; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    int uniquePaths(int m, int n) {
        return C[m+n-2][n-1];
    }
};
