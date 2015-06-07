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
    int countNodes(TreeNode* root) {
        if (root == NULL)   return 0;
        int l = 0, r = 0;
        for (TreeNode *p = root; p; p = p->left)
            l++;
        for (TreeNode *p = root; p; p = p->right)
            r++;
        if (l == r) // full tree
            return (1<<l) - 1;
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
