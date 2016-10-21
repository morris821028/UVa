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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (root == NULL)
            return ret;
        queue<TreeNode*> Q;
        Q.push(root);
        int it = 0;
        while (!Q.empty()) {
            vector<int> lv;
            TreeNode *u;
            queue<TreeNode*> NQ;
            it++;
            while (!Q.empty()) {
                u =  Q.front(), Q.pop();
                lv.push_back(u->val);
                if (u->left)
                    NQ.push(u->left);
                if (u->right)
                   NQ.push(u->right);
            }
            if (it%2 == 0)
                reverse(lv.begin(), lv.end());
            ret.push_back(lv);
            Q = NQ;
        }
        return ret;
    }
};
