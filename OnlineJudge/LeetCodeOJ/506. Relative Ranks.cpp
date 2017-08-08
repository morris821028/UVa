class Solution {
public:
    string int2str(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    vector<string> findRelativeRanks(vector<int>& A) {
        vector<int> B(A.begin(), A.end());
        sort(B.begin(), B.end());
        
        map<int, string> R;
        {
            string medal[] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
            int n = B.size();
            
            for (int i = n-1, j = 0; i >= 0; i--, j++) {
                if (j < 3)
                    R[B[i]] = medal[j];
                else
                    R[B[i]] = int2str(j+1);
            }
        }
        
        vector<string> ret;
        for (auto e: A)
            ret.push_back(R[e]);
        return ret;
    }
};
