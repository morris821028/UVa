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
    // morris traversal
    void reverse(TreeNode *from, TreeNode *to) {
        if (from == to)
            return ;
        TreeNode *u, *v, *t;
        u = from, v = from->right;
        while (true) {
            t = v->right;
            v->right = u;
            u = v;
            v = t;
            if (u == to)
                break;
        }
    }
    void print(TreeNode *from, TreeNode *to, vector<int> &ret) {
        reverse(from, to);
        
        TreeNode *u = to;
        while (true) {
            ret.push_back(u->val);
            if (u == from)
                break;
            u = u->right;
        }
        
        reverse(to, from);
    }
    void postorder(TreeNode *root, vector<int> &ret) {
        TreeNode dump(-1);
        dump.left = root, dump.right = NULL;
        TreeNode *cur = &dump, *pre = NULL;
        while (cur != NULL) {
            if (cur->left == NULL) {
                cur = cur->right;
            } else {
                pre = cur->left;
                while (pre->right != NULL && pre->right != cur)
                    pre = pre->right;
                if (pre->right == NULL) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    print(cur->left, pre, ret);
                    pre->right = NULL;
                    cur = cur->right;
                }
            }
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        postorder(root, ret);
        return ret;
    }
};
