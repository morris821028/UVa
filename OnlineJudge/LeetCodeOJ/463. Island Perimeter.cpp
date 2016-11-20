class Solution {
public:
    int islandPerimeter(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();
        int ret = 0;
        const int dx[4] = {0, 0, 1, -1};
        const int dy[4] = {1, -1, 0, 0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 0)
                    continue;
                
                for (int k = 0; k < 4; k++) {
                    int tx = i + dx[k], ty = j + dy[k];
                    if (tx < 0 || ty < 0 || tx >= n || ty >= m) {
                        ret++;
                        continue;
                    }
                    ret += g[tx][ty] == 0;
                }
            }
        }
        return ret;
    }
};
