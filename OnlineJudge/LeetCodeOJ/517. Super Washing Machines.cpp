class Solution {
public:
    int findMinMoves(vector<int>& M) {
        int n = M.size();
        int sum = 0, ret = 0;
        for (int i = 0; i < n; i++)
            sum += M[i];
        if (sum % n)
            return -1;
        vector<int> S(n, 0);
        for (int i = 0, s = 0; i < n; i++)
            s += M[i], S[i] = s;
        int avg = S[n-1] / n;
        for (int i = 0; i < n; i++) {
            // right to left
            int lpass = (i ? S[i-1] : 0) - avg * i;
            // left to right
            int rpass = (S[n-1] - S[i]) - avg * (n-i-1);
            if (lpass > 0 && rpass > 0)
                ret = max(ret, max(lpass, rpass));
            else if (lpass < 0 && rpass < 0)
                ret = max(ret, -lpass-rpass);
            else
                ret = max(ret, max(abs(lpass), abs(rpass)));
        }
        return ret;
    }
};
