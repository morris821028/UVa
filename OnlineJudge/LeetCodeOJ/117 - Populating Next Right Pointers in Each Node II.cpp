#include <bits/stdc++.h> 
using namespace std;

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
 
struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
 
class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *u, *v, *next_level;
        u = root;
		if (u) u->next = NULL;
        while (u) {
        	next_level = NULL, v = NULL;
        	while (u) {
        		if (u->left != NULL) {
        			if (next_level == NULL)
        				next_level = u->left;
        			if (v != NULL)
        				v->next = u->left, v = v->next;
        			else
        				v = u->left;
        		}
        		if (u->right != NULL) {
        			if (next_level == NULL)
        				next_level = u->right;
        			if (v != NULL)
        				v->next = u->right, v = v->next;
        			else
        				v = u->right;
        		}
        		u = u->next;
        	}
        	if (v != NULL)
        		v->next = NULL;
        	u = next_level;
        }
    }
};

int main() {
	Solution s;
	return 0;
}
