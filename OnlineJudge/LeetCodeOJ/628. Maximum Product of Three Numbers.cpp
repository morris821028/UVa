class Solution {
public:
    int maximumProduct(vector<int>& A) {
        sort(A.begin(), A.end());
        
        int hasZero = 0;
        for (auto x: A)
            hasZero |= x == 0;
        
        vector<int> neg, pos;
        int n = A.size();
        for (int i = 0; i < n; i++) {
            if (A[i] < 0)
                neg.push_back(A[i]);
        }
        
        for (int i = n-1; i >= 0; i--) {
            if (A[i] > 0)
                pos.push_back(A[i]);
        }
                
        int ret = INT_MIN;
        if (hasZero)    ret = 0;
        for (int i = 0; i <= 3; i++) {
            if (i == 0 && neg.size() >= 3)
                ret = max(ret, neg[neg.size()-1]*neg[neg.size()-2]*neg[neg.size()-3]);
            else if (i == 1 && neg.size() >= 2 && pos.size() >= 1)
                ret = max(ret, neg[0]*neg[1]*pos[0]);
            else if (i == 2 && neg.size() >= 1 && pos.size() >= 2)
                ret = max(ret, neg[neg.size()-1]*pos[0]*pos[1]);
            else if (i == 3 && pos.size() >= 3)
                ret = max(ret, pos[0]*pos[1]*pos[2]);
        }
        return ret;
    }
};
