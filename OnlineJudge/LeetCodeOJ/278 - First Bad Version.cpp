// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, r = n;
        int ret = 0;
        while (l <= r) {
            int mid = l + (r - l)/2;
            if (!isBadVersion(mid))
                l = mid+1, ret = mid;
            else
                r = mid-1;
        }
        return ret + 1;
    }
};
