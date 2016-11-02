/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    void midOfList(ListNode *begin, ListNode *end, ListNode **p) {
        ListNode *v1 = begin, *v2 = begin->next;
        while (v1 != end && v2 != end) {
            v1 = v1->next;
            v2 = v2->next;
            if (v2 == end)
                break;
            v2 = v2->next;
        }
        *p = v1;
    }
    TreeNode* build(ListNode *begin, ListNode *end) {
        if (begin == NULL || begin == end)
            return NULL;
        ListNode *p;
        midOfList(begin, end, &p);
        TreeNode *u = new TreeNode(p->val);
        u->left = build(begin, p);
        u->right = build(p->next, end);
        return u;
    }
    TreeNode* sortedListToBST(ListNode *head) {
        return build(head, NULL);
    }
};
