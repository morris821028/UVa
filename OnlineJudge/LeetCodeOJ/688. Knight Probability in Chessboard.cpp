class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        double dp[2][32][32] = {}, ret = 0;
        int p = 0, q = 1;
        dp[0][r][c] = 1;
        const int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
        const int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
        for (int i = 0; i < K; i++) {
            memset(dp[q], 0, sizeof(dp[q]));
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (dp[p][j][k] == 0)
                        continue;
                    double t = dp[p][j][k]/8;
                    for (int d = 0; d < 8; d++) {
                        int tx = j+dx[d], ty = k+dy[d];
                        if (tx >= 0 && ty >= 0 && tx < N && ty < N)
                            dp[q][tx][ty] += t; 
                    }
                }
            }
            p = 1-p, q = 1-q;
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                ret += dp[p][i][j];
        }
        return ret;
    }
};
