#include <bits/stdc++.h> 
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
	void dfs(TreeNode* u, pair<int, int> &ret) {
		ret = pair<int, int>(-0x3f3f3f3f, -0x3f3f3f3f);
		if (u == NULL)
			return ;
		pair<int, int> r1, r2;
		dfs(u->left, r1);
		dfs(u->right, r2);
		ret.first = max(max(r1.first, r2.first), 0) + u->val;
		ret.second = max(r1.first + r2.first + u->val, max(r1.second, r2.second));
		ret.second = max(ret.second, max(r1.first, r2.first));
	}
    int maxPathSum(TreeNode* root) {
        pair<int, int> ret;
        dfs(root, ret);
        return max(ret.first, ret.second);
    }
};
int main() {
	return 0;	
}
