/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    stack<TreeNode*> stk;
    bool pick;
    BSTIterator(TreeNode *root) {
        while (root != NULL) {
            stk.push(root);
            root = root->left;
        }
        pick = stk.size() != 0;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if (pick)
            return true;
        if (stk.empty())
            return false;
        TreeNode *top = stk.top();
        stk.pop();
        if (top->right != NULL) {
            TreeNode *u = top->right;
            while (u != NULL) {
                stk.push(u);
                u = u->left;
            }
        }
        pick = stk.size() != 0;
        return pick;
    }

    /** @return the next smallest number */
    int next() {
        pick = false;
        return stk.top()->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
