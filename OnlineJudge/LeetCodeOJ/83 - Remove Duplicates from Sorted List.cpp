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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *u = head;
        while (u != NULL) {
            while (u->next != NULL && u->val == u->next->val) {
                ListNode *v = u->next;
                u->next = u->next->next;
                free(v);
            }
            u = u->next;
        }
        return head;
    }
};
