class Solution {
public:
    int n, m;
    void bfs(int sx, int sy, vector<vector<char>> &g, vector<vector<int>> &used) {
        queue<int> X, Y;
        X.push(sx), Y.push(sy);
        used[sx][sy] = 1;
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        while (!X.empty()) {
            int x = X.front();
            int y = Y.front();
            X.pop(), Y.pop();
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i], ty = y + dy[i];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if (used[tx][ty] || g[tx][ty] != '1')
                    continue;
                used[tx][ty] = 1;
                X.push(tx), Y.push(ty);
            }
        }
    }
    int numIslands(vector<vector<char>>& g) {
        n = g.size();
        if (n == 0)
            return 0;
         m = g[0].size();
        vector<vector<int>> used(n, vector<int>(m, 0));
        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (used[i][j] == 0 && g[i][j] == '1') {
                    bfs(i, j, g, used);
                    ret++; 
                }
            }
        }
        return ret;
    }
};
