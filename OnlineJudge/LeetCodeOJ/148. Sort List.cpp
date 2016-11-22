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
    void split(ListNode* &p, ListNode* &q, ListNode *head) {
        ListNode *u, *v;
        u = head, v = head->next;
        if (v != NULL)
        	v = v->next;
        while (v != NULL) {
            u = u->next;
            v = v->next;
            if (v != NULL)
                v = v->next;
        }
        p = head;
        if (u != NULL) {
            q = u->next;
            u->next = NULL;
        } else {
            q = NULL;
        }
    }
    ListNode* merge(ListNode *p, ListNode *q) {
        if (p == NULL)
            return q;
        if (q == NULL)
            return p;
        ListNode *ret = NULL, *select, *t = NULL;
        while (p != NULL && q != NULL) {
            if (p->val < q->val)
                select = p, p = p->next;
            else
                select = q, q = q->next;
            if (ret == NULL)
                ret = select, t = ret;
            else
                t->next = select, t = t->next;
        }
        if (p != NULL)
            t->next = p;
        if (q != NULL)
            t->next = q;
        return ret;
    }
    void print(ListNode *head) {
    	while (head)
			printf("%d ", head->val), head = head->next;
		puts("-");
	}
    ListNode* MergeSort(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *p, *q;
        split(p, q, head);
        p = MergeSort(p);
        q = MergeSort(q);
        return merge(p, q);
    }
    ListNode* sortList(ListNode* head) {
        return MergeSort(head);
    }
};
