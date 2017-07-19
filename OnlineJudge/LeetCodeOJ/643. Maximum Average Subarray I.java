public class Solution {
    public double findMaxAverage(int[] nums, int k) {
        int n = nums.length;
        double ret;
        double sum = 0.0;
        for (int i = 0; i < k; i++)   
            sum += nums[i];
        ret = sum;
        for (int i = k; i < n; i++) {
            sum += nums[i] - nums[i-k];
            if (sum > ret)
                ret = sum;
        }
        return ret / k;
    }
}
