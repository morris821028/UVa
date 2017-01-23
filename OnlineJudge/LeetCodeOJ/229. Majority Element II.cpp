class Solution {
public:
    vector<int> majorityElement(vector<int>& A) {
        int x1 = -1, x2 = -1;
        int c1 = 0, c2 = 0;
        int n = A.size();
        for (auto x : A) {
            if (c1 && x1 == x)
                c1++;
            else if (c2 && x2 == x)
                c2++;
            else if (c1 == 0)
                x1 = x, c1 = 1;
            else if (c2 == 0)
                x2 = x, c2 = 1;
            else
                c1--, c2--;
        }
        vector<int> ret;
        if (c1) {
            int c = 0;
            for (auto x : A)
                c += x == x1;
            if (c > n/3)
                ret.push_back(x1);
        }
        if (c2) {
            int c = 0;
            for (auto x : A)
                c += x == x2;
            if (c > n/3)
                ret.push_back(x2);
        }
        return ret;
    }
};
