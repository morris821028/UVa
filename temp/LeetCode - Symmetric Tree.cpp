#include <stdio.h>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int myTest(TreeNode *u, TreeNode *v) {
        if ((u == NULL && v != NULL) || (u != NULL && v == NULL))
            return 0;
        if (u == NULL && v == NULL)
        	return 1;
        if (u->val != v->val)
        	return 0;
        return myTest(u->left, v->right) && myTest(u->right, v->left);
    }
    bool isSymmetric(TreeNode *root) {
        if (root == NULL)
            return true;
        return myTest(root->left, root->right);
    }
};

int main() {
	return 0;
}
