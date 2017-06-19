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
    string int2string(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    string tree2str(TreeNode* t) {
        if (t == NULL)
            return "";
        if (t->left == NULL && t->right == NULL)
            return int2string(t->val);
        if (t->right != NULL)
            return int2string(t->val) + "(" + tree2str(t->left) + ")" + "(" + tree2str(t->right) + ")";
        return int2string(t->val) + "(" + tree2str(t->left) + ")";
    }
};
