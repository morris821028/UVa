class Solution {
public:
    bool canPlaceFlowers(vector<int>& f, int n) {
        int m = f.size();
        for (int i = 0; i < m && n; i++) {
            if (f[i] == 1) {
                i++;
                continue;
            }
            if (f[i] == 0 && (i == m-1 || f[i+1] == 0)) {
                f[i] = 1, i++;
                n--;
            }
        }
        return n == 0;
    }
};
