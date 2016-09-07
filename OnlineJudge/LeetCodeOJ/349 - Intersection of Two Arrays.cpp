class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        nums1.resize(unique(nums1.begin(), nums1.end()) - nums1.begin());
        sort(nums2.begin(), nums2.end());
        nums2.resize(unique(nums2.begin(), nums2.end()) - nums2.begin());
        vector<int> ret;
        int p = 0, q = 0;
        while (p < nums1.size() && q < nums2.size()) {
            if (nums1[p] == nums2[q])
                ret.push_back(nums1[p]), p++, q++;
            else if (nums1[p] < nums2[q])
                p++;
            else
                q++;
        }
        return ret;
    }
};
