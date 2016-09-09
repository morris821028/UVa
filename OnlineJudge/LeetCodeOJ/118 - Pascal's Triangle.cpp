class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        if (numRows == 0)
            return ret;
        ret.push_back(vector<int>(1, 1));
        for (int i = 1; i < numRows; i++) {
            vector<int> t;
            t.push_back(1);
            for (int j = 1; j < i; j++)
                t.push_back(ret[i-1][j-1]+ret[i-1][j]);
            t.push_back(1);
            ret.push_back(t);
        }
        return ret;
    }
};
