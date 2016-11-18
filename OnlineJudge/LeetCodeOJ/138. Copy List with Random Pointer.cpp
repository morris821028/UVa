/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    void copy(RandomListNode *head) {
        RandomListNode *u = head, *v;
        while (u != NULL) {
            RandomListNode *tmp = new RandomListNode(u->label);
            v = u->next;
            u->next = tmp, tmp->next = v;
            u = v;
        }
    }
    void copyRandom(RandomListNode *head) {
        RandomListNode *u = head, *v;
        while (u != NULL) {
            v = u->next->next;
            if (u->random != NULL)
                u->next->random = u->random->next;
            u = v;
        }
    }
    RandomListNode* shrink(RandomListNode *head) {
        RandomListNode *ret = head->next;
        RandomListNode *u = ret, *v = head;
        while (u) {
            RandomListNode *tmp = u->next;
            v->next = tmp;
            if (tmp != NULL)
                u->next = u->next->next;
            u = u->next;
            v = v->next;
        }
        return ret;
    }
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL)
            return NULL;
        copy(head);
        copyRandom(head);
        return shrink(head);
    }
};
