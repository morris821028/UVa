class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ret;
        deque<pair<int, int>> Q;
        int top = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (!Q.empty() && Q.front().first <= i - k)
                Q.pop_front();
            while (!Q.empty() && Q.back().second < nums[i])
                Q.pop_back();
            Q.push_back(make_pair(i, nums[i]));
            if (i >= k-1)
                ret.push_back(Q.front().second);
        }
        return ret;
    }
};
