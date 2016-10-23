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
    int idx;
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int l, int r) {
        if (l > r)
            return NULL;
        if (l == r) {
            idx++;
            return new TreeNode(inorder[l]);
        }
        int t = preorder[idx++], pos = -1;
        for (int i = l; i <= r; i++) {
            if (inorder[i] == t) {
                pos = i;
                break;   
            }
        }
        TreeNode *ret = new TreeNode(t);
        ret->left = dfs(preorder, inorder, l, pos-1);
        ret->right = dfs(preorder, inorder, pos+1, r);
        return ret;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0)
            return NULL;
        idx = 0;
        return dfs(preorder, inorder, 0, n-1);
    }
};
