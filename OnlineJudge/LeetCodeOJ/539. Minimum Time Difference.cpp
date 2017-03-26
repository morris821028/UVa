class Solution {
public:
    int findMinDifference(vector<string>& T) {
        int n = T.size();
        vector<int> A(n);
        for (int i = 0; i < n; i++) {
            int a, b;
            sscanf(T[i].c_str(), "%d:%d", &a, &b);
            A[i] = a*60 + b;
        }
        sort(A.begin(), A.end());
        int ret = INT_MAX;
        for (int i = 0, j = n-1; i < n; j = i++) {
            int diff = abs(A[i]-A[j]);
            ret = min(ret, diff);
            ret = min(ret, 60*24 - diff);
        }
        return ret;
    }
};
