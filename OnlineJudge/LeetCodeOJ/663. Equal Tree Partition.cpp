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
    int dp[32767][2];
    int sumTree(TreeNode *u, int &dpIdx) {
        if (u == NULL)
            return 0;
        int t = dpIdx++;
        dp[t][0] = sumTree(u->left, dpIdx);
        dp[t][1] = sumTree(u->right, dpIdx);
        return u->val + dp[t][0] + dp[t][1];
    }
    bool dfs(TreeNode *u, int target, int sum, int &dpIdx) {
        if (u == NULL)
            return false;
        if (sum == target && dpIdx)
            return true;        
        int t = dpIdx++;
        if (dfs(u->left, target, sum + u->val + dp[t][1], dpIdx))
            return true;
        if (dfs(u->right, target, sum + u->val + dp[t][0], dpIdx))
            return true;
        return false;
    }
    bool checkEqualTree(TreeNode* root) {
        int dpIdx = 0;
        int sum = sumTree(root, dpIdx);
        if (sum%2)
            return false;
        dpIdx = 0;
        return dfs(root, sum/2, 0, dpIdx);
    }
};
