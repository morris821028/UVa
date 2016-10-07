/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public int sum(TreeNode u, boolean isLeft) {
        if (u == null)
            return 0;
        if (u.left == null && u.right == null)
            return isLeft ? u.val : 0;
        int ret = 0;
        ret += sum(u.left, true);
        ret += sum(u.right, false);
        return ret;
    }
    public int sumOfLeftLeaves(TreeNode root) {
        return sum(root, false);
    }
}
