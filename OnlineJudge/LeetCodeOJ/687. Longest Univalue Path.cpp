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
    int dfs(TreeNode *u, TreeNode *p, int top, int &ret) {
        if (u == NULL)
            return 0;
        if (p && p->val != u->val)
            top = 0;
        int mxdep = 1, l, r;
        l = dfs(u->left, u, top+1, ret);
        r = dfs(u->right, u, top+1, ret);
        if (u->left && u->left->val == u->val)
            mxdep = max(mxdep, l+1);
        else
            l = 0;
        if (u->right && u->right->val == u->val)
            mxdep = max(mxdep, r+1);
        else
            r = 0;
        ret = max(ret, l+r);
        return mxdep;
    }
    int longestUnivaluePath(TreeNode* root) {
        int ret = 0;
        dfs(root, NULL, 0, ret);
        return ret;
    }
};
