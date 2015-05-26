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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int tot = 0, pos = 0;
        ListNode *curr = head, *prev = NULL;
        while (curr != NULL)
            tot++, curr = curr->next;
        pos = tot - n + 1;
        curr = head, prev = NULL;
        while (curr != NULL && pos > 0) {
            pos--;
            if (pos == 0) {
                if (prev == NULL)   
                    head = curr->next;
                else                
                    prev->next = curr->next;
                delete curr;
            }
            prev = curr;
            curr = curr->next;
        }
        return head;
    }
};
