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
    void dfs(TreeNode *u, int &ret, int sum, int target) {
        if (u == NULL || ret)
            return ;
        if (u->left == NULL && u->right == NULL) {
            ret |= sum + u->val == target;
            return ;
        }
        dfs(u->left, ret, sum + u->val, target);
        dfs(u->right, ret, sum + u->val, target);
    }
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == NULL)
            return false;
        int ret = 0;
        dfs(root, ret, 0, sum);
        return ret;
    }
};
