class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int mxval = 0;
        int x = m, y = n;
        for (int i = 0; i < ops.size(); i++) {
            int a = ops[i][0], b = ops[i][1];
            if (a == 0 || b == 0)
                continue;
            mxval++;
            x = min(x, a);
            y = min(y, b);
        }
        return x * y;
    }
};
