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
    TreeNode* newNode() {
        TreeNode *u = (TreeNode*) malloc(sizeof(TreeNode));
        u->left = u->right = NULL;
        return u;
    }
    vector<TreeNode*> dfs(int l, int r) {
        if (l > r)
            return vector<TreeNode*>(1, NULL);
        vector<TreeNode*> ret;
        for (int i = l; i <= r; i++) {
            vector<TreeNode*> L = dfs(l, i-1);
            vector<TreeNode*> R = dfs(i+1, r);
            for (auto lu : L) {
                for (auto ru : R) {
                    TreeNode *u = newNode();
                    u->val = i;
                    u->left = lu, u->right = ru;
                    ret.push_back(u);
                }
            }
        }
        return ret;
    }
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0)
            return vector<TreeNode*>();
        return dfs(1, n);
    }
};
