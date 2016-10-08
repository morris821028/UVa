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
    ListNode *getIntersectionNode(ListNode *pA, ListNode *pB) {
        if (pA == NULL || pB == NULL)
            return NULL;
        ListNode *hA = pA, *hB = pB;
        int acnt = 0, bcnt = 0;
        for (; acnt < 2 && bcnt < 2;) {
            if (pA == pB)
                return pA;
            pA = pA->next;
            pB = pB->next;
            if (pA == NULL) pA = hB, acnt++;
            if (pB == NULL) pB = hA, bcnt++;
        }
        return NULL;
    }
};
