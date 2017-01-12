class Solution {
public:
    string int2str(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    vector<string> summaryRanges(vector<int>& A) {
        int n = A.size();
        vector<string> ret;
        for (int i = 0; i < n; ) {
            int l = A[i], r = A[i];
            i++;
            while (i < n && A[i] == A[i-1]+1)
                r = A[i], i++;
            if (l == r)
                ret.push_back(int2str(l));
            else
                ret.push_back(int2str(l) + "->" + int2str(r));
        }
        return ret;
    }
};
