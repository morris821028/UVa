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
    bool isBalanced(TreeNode* root) {
        int ret = 1;
        testBalanced(root, ret);
        return ret == 1;
    }
private:
    int testBalanced(TreeNode* u, int &ret) {
        if (u == NULL)  return 0;
        int l = testBalanced(u->left, ret);
        int r = testBalanced(u->right, ret);
        ret &= abs(l - r) <= 1;
        return max(l, r)+1;
    }
};
