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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        TreeNode *u = root, *prev = NULL;
        while (u != NULL) {
            if (u->left == NULL) {
                ret.push_back(u->val);
                u = u->right;
            } else {
                prev = u->left;
                while (prev->right != NULL && prev->right != u)
                    prev = prev->right;
                if (prev->right == NULL) {
                    prev->right = u;
                    u = u->left;
                } else {
                    prev->right = NULL;
                    ret.push_back(u->val);
                    u = u->right;
                }
            }
        }
        return ret;
    }
};
