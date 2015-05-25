#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    void recoverTree(TreeNode* root) {
        if (root == NULL)
            return;
        
        TreeNode *curr, *prev, *pred = NULL; // predecessor
        TreeNode *err1 = NULL, *err2 = NULL;
        
        curr = root;
        while (curr != NULL) {
            if (curr->left == NULL) {
                // check valid
                if (pred != NULL && pred->val > curr->val) {
                    err2 = curr;
                    if (err1 == NULL)   err1 = pred;
                }
                
                pred = curr;
                curr = curr->right;
            } else {
                prev = curr->left;
                while (prev->right != NULL && prev->right != curr)
                    prev = prev->right;
                
                if (prev->right == NULL) {
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // check valid
                    if (pred != NULL && pred->val > curr->val) {
                        err2 = curr;
                        if (err1 == NULL)   err1 = pred;
                    }
                    
                    prev->right = NULL;
                    pred = curr;
                    curr = curr->right;
                }
            }
        }
        
        if (err1 && err2)
            swap(err1->val, err2->val);
    }
};

int main() {
    return 0;
}