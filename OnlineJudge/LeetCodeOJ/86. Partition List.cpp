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
    ListNode* partition(ListNode* head, int x) {
        ListNode *l1 = NULL, *l2 = NULL;
        ListNode *p1 = NULL, *p2 = NULL;
        while (head != NULL) {
            if (head->val < x) {
                if (l1 == NULL)
                    l1 = head;
                else
                    p1->next = head;
                p1 = head;
            } else {
                if (l2 == NULL)
                    l2 = head;
                else
                    p2->next = head;
                p2 = head;
            }
            head = head->next;
        }
        if (p1 != NULL)
            p1->next = l2;
        if (p2 != NULL)
            p2->next = NULL;
        if (l1 == NULL)
            l1 = l2;
        return l1;
    }
};
