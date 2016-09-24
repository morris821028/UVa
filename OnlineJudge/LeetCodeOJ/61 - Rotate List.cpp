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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || k == 0)
            return head;
        int size = 0;
        ListNode *tail, *u, *v;
        for (u = head; u != NULL; tail = u, u = u->next)
            size++;
        size = ((size - k)%size + size)%size;
        if (size == 0)
            return head;
        for (u = head, v = NULL; u != NULL && size != 0; u = u->next)
            v = u, size--;
        if (v != NULL)
            v->next = NULL;
        tail->next = head;
        head = u;
        return head;
    }
};
