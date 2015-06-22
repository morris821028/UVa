class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ret = 0;
        int mn = INT_MAX;
        for (int i = 0; i < prices.size(); i++) {
            mn = min(mn, prices[i]);
            ret = max(ret, prices[i] - mn);
        }
        return ret;
    }
};
