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
        if (head == NULL)
            return NULL;
        ListNode *ret = NULL, *prev = NULL;
        while (head != NULL) {
            int cnt = 0;
            ListNode *be = head;
            while (head != NULL && head->val == be->val)
                cnt++, head = head->next;
            if (cnt == 1) {
                if (ret == NULL)
                    ret = be;
                else
                    prev->next = be;
                prev = be;
            }
        }
        if (prev != NULL)
            prev->next = NULL;
        return ret;
    }
};
