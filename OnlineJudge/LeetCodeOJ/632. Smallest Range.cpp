class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& A) {
        set< pair<int, int> > S;
        const int MAXV = 131072;
        int n = A.size();
        vector<int> B(n, 0);
        for (int i = 0; i < n; i++)
            S.insert(make_pair(A[i][0], i));
        
        pair<int, int> ret(-MAXV, MAXV);
        int mnRange = MAXV*2;
        while (!S.empty()) {
            pair<int, int> mn = *S.begin();
            pair<int, int> mx = *S.rbegin();
            if (mx.first-mn.first < mnRange) {
                mnRange = mx.first-mn.first;
                ret = make_pair(mn.first, mx.first);
            }
            int i = mn.second;
            if (B[i] == A[i].size()-1)
                break;
            S.erase(S.begin());
            B[i]++;
            S.insert(make_pair(A[i][B[i]], i));
        }
        vector<int> t(2);
        t[0] = ret.first;
        t[1] = ret.second;
        return t;
    }
};
