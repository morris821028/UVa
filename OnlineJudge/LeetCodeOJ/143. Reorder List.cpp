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
    void split(ListNode *head, ListNode* &p, ListNode* &q) {
        p = head, q = head->next;
        while (p != NULL && q != NULL) {
            p = p->next, q = q->next;
            if (q != NULL)
                q = q->next;
        }
        if (p != NULL) {
            q = p->next;
            p->next = NULL;
        } else {
            q = NULL;
        }
        p = head;
    }
    ListNode* reverse(ListNode *p) {
        ListNode *ret = NULL;
        while (p != NULL) {
            ListNode *next = p->next;
            p->next = ret;
            ret = p;
            p = next;
        }
        return ret;
    }
    void merge(ListNode *p, ListNode *q) {
        while (p != NULL && q != NULL) {
            ListNode *np, *nq;
            np = p->next;
            nq = q->next;
            p->next = q;
            q->next = np;
            p = np, q = nq;
        }
    }
    void reorderList(ListNode* head) {
        if (head == NULL)
            return ;
        ListNode *p, *q;
        split(head, p, q);
        q = reverse(q);
        merge(p, q);
    }
};
