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
    void reverse(ListNode *p, ListNode *q) {
        ListNode *u, *v;
        u = p, v = p->next;
        while (v != NULL && u != q) {
            ListNode *t = v->next;
            v->next = u;
            u = v, v = t;
        }
        p->next = NULL;
    }
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *p, *q, *prev_p, *next_q;
        p = head, prev_p = NULL;
        q = head, next_q = NULL;
        for (int i = 1; i < m && p != NULL; i++)
            prev_p = p, p = p->next;
        for (int i = 1; i < n && q != NULL; i++)
            q = q->next;
        next_q = q->next;
        reverse(p, q);
        if (prev_p == NULL) 
            head = q;
        else
            prev_p->next = q;
        p->next = next_q;
        return head;
    }
};
