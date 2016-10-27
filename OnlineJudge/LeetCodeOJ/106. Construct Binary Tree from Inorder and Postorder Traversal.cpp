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
    TreeNode* dfs(vector<int>& postorder, vector<int>& inorder, int l, int r) {
        if (l > r)
            return NULL;
        if (l == r) {
            idx--;
            return new TreeNode(inorder[l]);
        }
        int t = postorder[idx--], pos = -1;
        for (int i = l; i <= r; i++) {
            if (inorder[i] == t) {
                pos = i;
                break;   
            }
        }
        TreeNode *ret = new TreeNode(t);
        ret->right = dfs(postorder, inorder, pos+1, r);
        ret->left = dfs(postorder, inorder, l, pos-1);
        return ret;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();
        if (n == 0)
            return NULL;
        idx = n-1;
        return dfs(postorder, inorder, 0, n-1);
    }
};
