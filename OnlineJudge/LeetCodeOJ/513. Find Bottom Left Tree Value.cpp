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
    TreeNode* dfs(TreeNode *u, int dep, int &mxdep) {
        if (u == NULL)
            return NULL;
        TreeNode *ret = NULL, *t;
        if (dep > mxdep)
            mxdep = dep, ret = u;
        if (u->left != NULL) {
            t = dfs(u->left, dep+1, mxdep);
            if (t != NULL)
                ret = t;
        }
        if (u->right != NULL) {
            t = dfs(u->right, dep+1, mxdep);
            if (t != NULL)
                ret = t;
        }
        return ret;
    }
    int findBottomLeftValue(TreeNode* root) {
        int mxdep = -1;
        return dfs(root, 0, mxdep)->val;
    }
};
