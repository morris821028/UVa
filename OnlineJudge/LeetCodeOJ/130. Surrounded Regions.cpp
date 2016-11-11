class Solution {
public:
    int n, m;
    int bfs(int x, int y, vector< vector<int> > &used, vector<vector<char>>& board) {
        queue<int> X, Y;
        X.push(x), Y.push(y);
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int ret = 1;
        while (!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            if (x == 0 || y == 0 || x == n-1 || y == m-1)
                ret = 0;
            for (int i = 0; i < 4; i++) {
                int tx, ty;
                tx = x + dx[i], ty = y + dy[i];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m || board[tx][ty] == 'X')
                    continue;
                if (used[tx][ty] == 1)
                    continue;
                used[tx][ty] = 1;
                X.push(tx), Y.push(ty);
            }
        }
        return ret;
    }
    void color(int x, int y, vector< vector<int> > &used, vector<vector<char>>& board) {
        queue<int> X, Y;
        X.push(x), Y.push(y);
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        board[x][y] = 'X';
        while (!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            for (int i = 0; i < 4; i++) {
                int tx, ty;
                tx = x + dx[i], ty = y + dy[i];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m || board[tx][ty] == 'X')
                    continue;
                if (used[tx][ty] == 2)
                    continue;
                used[tx][ty] = 2, board[tx][ty] = 'X';
                X.push(tx), Y.push(ty);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0)
            return ;
        n = board.size(), m = board[0].size();
        vector< vector<int> > used(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'X')
                    continue;
                if (used[i][j])
                    continue;
                int valid = bfs(i, j, used, board);
                if (valid)
                    color(i, j, used, board);
            }
        }
    }
};:
