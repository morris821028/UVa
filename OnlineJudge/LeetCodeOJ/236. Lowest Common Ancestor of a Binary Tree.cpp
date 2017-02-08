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
    TreeNode* LCA(TreeNode *u, TreeNode *p, TreeNode *q, int &state) {
        if (u == NULL)
            return NULL;
        int l = 0, r = 0;
        TreeNode *lson = LCA(u->left, p, q, l);
        if (l == 3) {
            state = 3;
            return lson;
        }
        TreeNode *rson = LCA(u->right, p, q, r);
        if (r == 3) {
            state = 3;
            return rson;
        }
        state = l | r;
        if (u == p)
            state |= 1;
        if (u == q)
            state |= 2;
        return (state == 3) ? u : NULL;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int state = 0;
        return LCA(root, p, q, state);
    }
};
