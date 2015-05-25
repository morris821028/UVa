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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *curr = NULL, *prev, *head;
        ListNode *ptr1, *ptr2;
        int carry = 0;
        
        ptr1 = l1, ptr2 = l2;
        while (ptr1 || ptr2 || carry) {
            prev = curr;
            int va = ptr1 ? ptr1->val : 0;
            int vb = ptr2 ? ptr2->val : 0;
            carry += va + vb;
            curr = new ListNode(carry%10);
            if (prev == NULL)
                head = curr;
            else
                prev->next = curr;
            carry /= 10;
            if (ptr1) ptr1 = ptr1->next;
            if (ptr2) ptr2 = ptr2->next;
        }
        
        return head;
    }
};
