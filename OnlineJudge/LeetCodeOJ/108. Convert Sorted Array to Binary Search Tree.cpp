/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* build(vector<int> &A, int l, int r) {
        if (l > r)
            return NULL;
        int mid = (l + r)/2;
        TreeNode *u = new TreeNode(A[mid]);
        u->left = build(A, l, mid-1);
        u->right = build(A, mid+1, r);
        return u;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size()-1);
    }
};
