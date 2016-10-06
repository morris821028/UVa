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
    string int2str(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    void dfs(vector<string> &ret, TreeNode *u, string path) {
        if (u == NULL)  return ;
        if (u->left == NULL && u->right == NULL) {
            if (path.length())
                path += "->";
            path += int2str(u->val);
            ret.push_back(path);
            return ;
        }
        if (path.length())
            path += "->";
        path += int2str(u->val);
        dfs(ret, u->left, path);
        dfs(ret, u->right, path);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        if (root == NULL)
            return ret;
        dfs(ret, root, "");
        return ret;
    }
};
