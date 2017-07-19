public class Solution {
    private double avg(int l, int r, int S[]) {
        return (double) (S[r] - S[l]) / (r - l);
    }
    public double findMaxAverage(int[] A, int k) {
        int n = A.length;
        int[] S = new int[n+1];
        int[] Q = new int[n+1];
        
        S[0] = 0;
        for (int i = 1; i <= n; i++)
            S[i] = S[i-1] + A[i-1];
        
        double ret = S[n]/n;
        int l = 0, r = -1;
        for (int i = k; i <= n; i++) {
            int t = i - k;
            while (l < r && avg(Q[r], t, S) <= avg(Q[r-1], t, S))
                r--;
            Q[++r] = t;
            while (l < r && avg(Q[l], i, S) <= avg(Q[l+1], i, S))
                l++;
            double tmp = avg(Q[l], i, S);
            if (tmp > ret)
                ret = tmp;
        }
        return ret;
    }
}
