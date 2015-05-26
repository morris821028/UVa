class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int) height.size() - 1;
        int ret = 0;
        while (left < right) {
            ret = max(ret, min(height[left], height[right]) * (right - left));
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return ret;
    }
};

