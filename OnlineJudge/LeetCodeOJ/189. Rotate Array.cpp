class Solution {
public:
    void reverse(vector<int> &A, int l, int r) {
        for (; l < r; l++, r--)
            swap(A[l], A[r]);
    }
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = (k%n + n)%n;
        reverse(nums, 0, n-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, n-1);
    }
};
