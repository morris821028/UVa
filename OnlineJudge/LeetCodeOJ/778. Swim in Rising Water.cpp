class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        set<pair<int, int>> Q;
        vector<int> visited(n*m, 0);
        Q.insert(make_pair(0, 0));

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        int t = 0;
        while (!Q.empty()) {
            auto e = *Q.begin();
            Q.erase(Q.begin());
            int x = e.second / m;
            int y = e.second % m;

            t = max(t, grid[x][y]);
            if (x == n-1 && y == m-1)
                return t;

            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m)
                    continue;
                int v = tx * m + ty;
                if (visited[v] == 0) {
                    visited[v] = 1;
                    Q.insert(make_pair(grid[tx][ty], v));
                }
            }
        }
        
        return t;
    }
};
