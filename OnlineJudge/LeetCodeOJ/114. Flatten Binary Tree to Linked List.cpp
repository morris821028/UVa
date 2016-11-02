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
    void flatten(TreeNode* root) {
        TreeNode *u = root;
        while (u != NULL) {
            if (u->left != NULL) {
                TreeNode *tmp = u->left;
                while (tmp->right != NULL)
                    tmp = tmp->right;
                tmp->right = u->right;
                u->right = u->left;
                u->left = NULL;
            }
            u = u->right;
        }
    }
};
