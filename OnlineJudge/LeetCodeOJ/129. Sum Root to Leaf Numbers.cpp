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
    int dfs(TreeNode *u, int sum) {
        if (u == NULL)  return 0;
        sum = sum * 10 + u->val;
        if (u->left == NULL && u->right == NULL)
            return sum;
        return dfs(u->left, sum) + dfs(u->right, sum);
    }
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
};
