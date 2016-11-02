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
    void dfs(TreeNode *u, int target, int sum, vector<int> &path, 
                vector<vector<int>> &ret) {
        if (u == NULL)
            return ;
        path.push_back(u->val);
        sum += u->val;
        if (u->left == NULL && u->right == NULL) {
            if (sum == target)
                ret.push_back(path);
            path.pop_back();
            return ;
        }
        if (u->left != NULL)
            dfs(u->left, target, sum, path, ret);
        if (u->right != NULL)
            dfs(u->right, target, sum, path, ret);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        vector<int> path;
        dfs(root, sum, 0, path, ret);
        return ret;
    }
};
