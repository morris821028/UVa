class Solution {
public:
    int reversePairs(vector<int>& A) {
        vector<int> B(A.begin(), A.end());
        sort(B.begin(), B.end());
        B.resize(unique(B.begin(), B.end()) - B.begin());
        
        int n = A.size(), ret = 0;
        vector<int> BIT(n+1, 0);
        for (int i = n-1; i >= 0; i--) {
            int u = A[i], v = -1;
            u = lower_bound(B.begin(), B.end(), u) - B.begin();
            int l = 0, r = B.size()-1;
            while (l <= r) {
                int mid = (l + r)/2;
                if (B[mid]*2LL < A[i])
                    v = mid, l = mid+1;
                else
                    r = mid-1;
            }
            u++, v++;
            int sum = 0;
            while (v)
                sum += BIT[v], v -= v&(-v);
            while (u <= n)
                BIT[u]++, u += u&(-u);
            ret += sum;
        }
        return ret;
    }
};
