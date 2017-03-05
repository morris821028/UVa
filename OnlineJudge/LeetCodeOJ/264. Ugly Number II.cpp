class Solution {
public:
    int nthUglyNumber(int n) {
        long long x[32767];
        int y[3] = {0, 0, 0};
        long long ret = 0;
        x[0] = 1;
        for (int i = 1; i < n; i++) {
            ret = min(x[y[0]]*2, x[y[1]]*3);
            ret = min(ret, x[y[2]]*5);
            x[i] = ret;
            while (x[y[0]]*2 <= ret)
                y[0]++;
            while (x[y[1]]*3 <= ret)
                y[1]++;
            while (x[y[2]]*5 <= ret)
                y[2]++;
        }
        return x[n-1];
    }
};
