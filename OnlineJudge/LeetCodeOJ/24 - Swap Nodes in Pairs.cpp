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
    ListNode* swapPairs(ListNode* head) {
        ListNode *rhead = head && head->next ? head->next : head;
        ListNode tmp(-1);
        ListNode *prev, *curr;
        
        curr = head, prev = &tmp;
        while (curr && curr->next) {
            prev->next = curr->next;
            curr->next = prev->next->next;
            prev->next->next = curr;
            prev = curr, curr = curr->next;
        }
        
        return rhead;
    }
};
