class Solution {
public:
    vector<int> countSmaller(vector<int>& A) {
        int n = A.size();
        vector<int> ret(n, 0);
        map<int, int> R;
        int size = 0;
        for (auto e: A) 
            R[e] = 0;
        for (auto &e: R) 
            e.second = ++size;
            
        vector<int> BIT(size+1, 0);
        for (int i = n-1; i >= 0; i--) {
            int x = R[A[i]]-1, sm = 0;
            while (x)
                sm += BIT[x], x -= x&(-x);
            x = R[A[i]];
            while (x <= size)
                BIT[x]++, x += x&(-x);
            ret[i] = sm;
        }
        return ret;
    }
};
