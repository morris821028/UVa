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
    void dfs(TreeNode* u, int &l, int &r, int &ret) {
        int v = u->val;
        int lmx, lmn, rmx, rmn;
        l = v, r = v;
        if (u->left != NULL) {
            dfs(u->left, lmn, lmx, ret);
            ret = min(ret, abs(v - lmx));
            l = min(lmn, l);
        }
        if (u->right != NULL) {
            dfs(u->right, rmn, rmx, ret);
            ret = min(ret, abs(v - rmn));
            r = max(rmx, r);
        }
        return ;
    }
    int getMinimumDifference(TreeNode* root) {
        if (root == NULL)
            return 0;
        int ret = INT_MAX, l, r;
        dfs(root, l, r, ret);
        return ret;
    }
};
