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
    TreeNode* dfs(TreeNode *u, int v, int d, int dep) {
        if (d == dep+1) {
            if (u == NULL) {
                return new TreeNode(v);
            }
            TreeNode *lson = new TreeNode(v);
            TreeNode *rson = new TreeNode(v);
            lson->left = u->left;
            rson->right = u->right;
            u->left = lson;
            u->right = rson;
            return u;
        }
        if (u == NULL)
            return u;
        dfs(u->left, v, d, dep+1);
        dfs(u->right, v, d, dep+1);
        return u;
    }
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode *lson = new TreeNode(v);
            lson->left = root;
            return lson;
        }
        return dfs(root, v, d, 1);
    }
};
