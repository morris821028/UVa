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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        queue<TreeNode*> Q;
        if (root == NULL)
            return ret;
        Q.push(root);
        while (!Q.empty()) {
            queue<TreeNode*> NQ;
            vector<int> level;
            while (!Q.empty()) {
                TreeNode *u = Q.front();
                Q.pop();
                if (u->left != NULL)
                    NQ.push(u->left);
                if (u->right != NULL)
                    NQ.push(u->right);
                level.push_back(u->val);
            }
            ret.push_back(level);
            Q = NQ;
        }
        return ret;
    }
};
