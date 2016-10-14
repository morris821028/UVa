public class Solution {
    class P implements Comparable<Object> {
        int x, y, val;
        public P(int x, int y, int val) {
            this.x = x;
            this.y = y;
            this.val = val;
        }
        @Override
        public int compareTo(Object obj) {
            if (! (obj instanceof P))
                return 0;
            P e = (P) obj;
            return val < e.val ? -1 : (val > e.val ? 1 : 0);
        }
    }
    public int longestIncreasingPath(int[][] g) {
        if (g == null || g.length == 0 || g[0].length == 0)
            return 0;
        int n = g.length;
        int m = g[0].length;
        P[] pts = new P[n*m];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                P pt = new P(i, j, g[i][j]);
                pts[i*m + j] = pt;
            }
        }

        Arrays.sort(pts);
        
        final int dx[] = {0, 0, 1, -1};
        final int dy[] = {1, -1, 0, 0};
        int[][] dp = new int[n][m];
        int ret = 0;
        for (int i = 0; i < pts.length; i++) {
            P t = pts[i];
            int mxdep = 1;
            for (int j = 0; j < 4; j++) {
                int tx = t.x + dx[j];
                int ty = t.y + dy[j];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if (g[tx][ty] < t.val) {
                    mxdep = Math.max(mxdep, dp[tx][ty]+1);
                }
            }
            dp[t.x][t.y] = mxdep;
            ret = Math.max(ret, mxdep);
        }
        return ret;
    }
}
