/*
	given only "access"
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node == NULL || node->next == NULL)
            return ;
        while (node && node->next) {
            node->val = node->next->val;
            if (node->next->next == NULL)
                node->next = NULL;
            node = node->next;
        }
    }
};
