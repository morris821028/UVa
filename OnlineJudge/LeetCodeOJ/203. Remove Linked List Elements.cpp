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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *ret = NULL, *pre = NULL;
        while (head != NULL) {
            ListNode *u = head->next;
            if (head->val == val) {
                if (pre != NULL)
                    pre->next = u;
                free(head);
            } else {
                if (ret == NULL)
                    ret = head;
                pre = head;
            }
            head = u;
        }
        return ret;
    }
};
