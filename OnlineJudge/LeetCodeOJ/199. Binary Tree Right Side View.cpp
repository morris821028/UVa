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
    int depth(TreeNode *u) {
        if (u == NULL)  return 0;
        return max(depth(u->left), depth(u->right))+1;
    }
    void dfs(TreeNode *u, vector<int> &ret, int dep) {
        if (u == NULL)
            return ;
        ret[dep] = u->val;
        dfs(u->left, ret, dep+1);
        dfs(u->right, ret, dep+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret(depth(root));
        dfs(root, ret, 0);
        return ret;
    }
};
