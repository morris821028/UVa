class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& A, int K) {
        vector<int> ret;
        int n = A.size();
        vector<int> L(n), R(n);
        vector<int64_t> P(n, 0), Q(n, 0);
        for (int i = 0; i < n; i++)
            P[i] = (i ? P[i-1] : 0) + A[i];
        for (int i = n-1; i >= 0; i--)
            Q[i] = (i != n-1 ? Q[i+1] : 0) + A[i];
        {
            L[K-1] = 0;
            int64_t mx = P[K-1], mxidx = 0;
            for (int i = K; i < n; i++) {
                if (P[i]-P[i-K] > mx)
                    mx = P[i]-P[i-K], mxidx = i-K+1;
                L[i] = mxidx;
            }
            
        }
        {
            R[n-K] = n-K;
            int64_t mx = Q[n-K], mxidx = n-K;
            for (int i = n-K-1; i >= 0; i--) {
                if (Q[i]-Q[i+K] > mx)
                    mx = Q[i]-Q[i+K], mxidx = i;
                R[i] = mxidx;
            }
        }
        
        int64_t mx = -(1LL<<60);
        for (int i = K; i <= n-K-K; i++) {
            int64_t sum = 0;
            sum += P[L[i-1]+K-1] - (L[i-1] ? P[L[i-1]-1] : 0);
            sum += P[R[i+K]+K-1] - (R[i+K] ? P[R[i+K]-1] : 0);
            sum += P[i+K-1] - P[i-1];
            if (sum > mx)
                mx = sum, ret = {L[i-1], i, R[i+K]};
            // printf("%d %d %d, %lld\n", L[i-1], i, R[i+K], sum);
        }
        
        return ret;
    }
};
