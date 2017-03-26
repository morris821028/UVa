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
    struct MM {
        int v[2];
        MM() {
            memset(v, 0, sizeof(v));
        }
        int &operator[](const int &x) {
            return v[x];
        }
    };
    int dfs1(TreeNode *u, map<TreeNode*, MM> &dp) {
        if (u == NULL)
            return 0;
        int ret = 0, l, r;
        dp[u][0] = l = dfs1(u->left, dp);
        dp[u][1] = r = dfs1(u->right, dp);
        ret = max(l, r);
        return ret+1;
    }
    int dfs2(TreeNode *u, map<TreeNode*, MM> &dp, int top) {
        if (u == NULL)
            return 0;
        int ret = 0, l = dp[u][0], r = dp[u][1];
        ret = max(ret, l+r+1);
        int lans = dfs2(u->left, dp, max(top+1, r+1));
        int rans = dfs2(u->right, dp, max(top+1, l+1));
        return max(ret, max(lans, rans));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == NULL)
            return 0;
        map<TreeNode*, MM> dp;
        dfs1(root, dp);
        return dfs2(root, dp, 0)-1;
    }
};
