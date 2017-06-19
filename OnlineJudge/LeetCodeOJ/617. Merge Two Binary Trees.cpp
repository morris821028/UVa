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
    TreeNode* dfs(TreeNode *L, TreeNode *R) {
        if (L == NULL && R == NULL)
            return NULL;
        TreeNode *ll, *lr, *rl, *rr;
        ll = lr = rl = rr = NULL;
        if (L == NULL)
            swap(L, R);
        if (L != NULL)
            ll = L->left, lr = L->right;
        if (R != NULL)
            rl = R->left, rr = R->right;
        if (L != NULL && R != NULL) {
            L->val += R->val;
            free(R);
        }
        L->left = dfs(ll, rl);
        L->right = dfs(lr, rr);
        return L;
    }
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        return dfs(t1, t2);
    }
};
