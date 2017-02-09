class Solution {
public:
    bool searchMatrix(vector<vector<int>>& A, int target) {
        int n = A.size();
        if (n == 0)
            return false;
        int m = A[0].size();
        int x = 0, y = m-1;
        while (x < n && y >= 0) {
            if (A[x][y] == target)
                return true;
            if (A[x][y] > target)
                y--;
            else
                x++;
        }
        return false;
    }
};
