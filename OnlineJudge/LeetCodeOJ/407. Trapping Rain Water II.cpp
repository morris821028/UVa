class Solution {
public:
	int n, m;
    int trapRainWater(vector< vector<int> > &H) {
        if (H.size() == 0 || H[0].size() == 0)
        	return 0;
        n = H.size(), m = H[0].size();
        set< pair<int, pair<int, int> > > Q;
        vector< vector<int> > used(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0 || i == n-1 || j == m-1) {
                    used[i][j] = 1;
                    Q.insert({H[i][j], {i, j}});
                }
            }
        }
        
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        long long ret = 0;
        while (!Q.empty()) {
            pair<int, pair<int, int> > u = *Q.begin();
            Q.erase(Q.begin());
            int x = u.second.first;
            int y = u.second.second;
            int h = u.first;
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m || used[tx][ty])
                    continue;
                if (H[tx][ty] < h) {
                    ret += h - H[tx][ty];
                    H[tx][ty] = h;
                }
                used[tx][ty] = 1;
                Q.insert({H[tx][ty], {tx, ty}});
            }
        }
		return ret;
    }
};
