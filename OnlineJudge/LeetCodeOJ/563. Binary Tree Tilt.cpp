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
    int dfs(TreeNode *u, int &sum) {
        if (u == NULL) {
            sum = 0;
            return 0;
        }
        int l, r, ret = 0;
        ret += dfs(u->left, l);
        ret += dfs(u->right, r);
        ret += abs(l-r);
        sum = l + r + u->val;
        return ret;
    }
    int findTilt(TreeNode* root) {
        int foo;
        return dfs(root, foo);
    }
};
