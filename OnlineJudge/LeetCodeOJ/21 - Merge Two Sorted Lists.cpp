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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL)     
            return l2;
        if (l2 == NULL)
            return l1;
            
        ListNode *head, *curr;
        
        if (l1->val < l2->val)
            head = l1, l1 = l1->next;
        else
            head = l2, l2 = l2->next;
        
        curr = head;
        while (l1 != NULL || l2 != NULL) {
            if (l1 == NULL) {
                curr->next = l2, l2 = NULL;
            } else if (l2 == NULL) {
                curr->next = l1, l1 = NULL;
            } else {
                if (l1->val < l2->val)
                    curr->next = l1, l1 = l1->next;
                else
                    curr->next = l2, l2 = l2->next;
            }
            curr = curr->next;
        }
        return head;
    }
};
