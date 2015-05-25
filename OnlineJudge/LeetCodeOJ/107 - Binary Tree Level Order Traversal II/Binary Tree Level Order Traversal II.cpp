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
    vector< vector<int> > levelOrderBottom(TreeNode* root) {
        vector< vector<int> > ret;
        vector< vector<TreeNode*> > Q;
        
        if (root == NULL)
            return ret;
        
        Q.push_back(vector<TreeNode*>(1, root));
        for (int i = 0; i < Q.size(); i++) {
            vector<int> level;
            
            int has = 0;
            for (int j = 0; j < Q[i].size(); j++) {
                level.push_back(Q[i][j]->val);
                has |= Q[i][j]->left || Q[i][j]->right;
            }
            ret.push_back(level);
            
            if (!has)
                break;
                
            Q.push_back(vector<TreeNode*>());
            for (int j = 0; j < Q[i].size(); j++) {
                if (Q[i][j]->left)  
                    Q[i+1].push_back(Q[i][j]->left);
                if (Q[i][j]->right)  
                    Q[i+1].push_back(Q[i][j]->right);
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};