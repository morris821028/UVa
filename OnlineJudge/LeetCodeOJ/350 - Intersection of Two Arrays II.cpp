class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> R1, R2;
        vector<int> ret;
        for (auto e: nums1)
            R1[e]++;
        for (auto e: nums2)
            R2[e]++;
        for (auto e: R2) {
            if (R1.count(e.first)) {
                int n = min(e.second, R1[e.first]);
                for (int i = 0; i < n; i++)
                    ret.push_back(e.first);
            }
        }
        return ret;
    }
};
