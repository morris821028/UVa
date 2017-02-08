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
    int dfs(TreeNode *u, int &k) {
        if (u->left != NULL) {
            int ret = dfs(u->left, k);
            if (k == 0)
                return ret;
        }
        k--;
        if (k == 0)
            return u->val;
        if (u->right != NULL) {
            int ret = dfs(u->right, k);
            if (k == 0)
                return ret;
        }
        return -1;
    }
    int kthSmallest(TreeNode* root, int k) {
        return dfs(root, k);
    }
};
