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
    void insert(ListNode* &head, ListNode *val) {
        if (head == NULL) {
            head = val;
            head->next = NULL;
            return ;
        }
        int t = val->val;
        ListNode *u = head;
        ListNode *prev = NULL, *next = u;
        while (u != NULL && u->val > t) {
            prev = u;
            u = u->next;
            next = u;
        }
        if (prev == NULL) {
            val->next = next;
            head = val;
        } else {
            prev->next = val;
            val->next = next;
        }
    }
    ListNode* reverse(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode *tmp, *ret = NULL;
        while (head != NULL) {
            tmp = head->next;
            head->next = ret;
            if (head != NULL)
                ret = head;
            head = tmp;
        }
        return ret;
    }
    ListNode* insertionSortList(ListNode* head) {
        ListNode *ret = NULL;
        while (head != NULL) {
            ListNode *tmp = head->next;
            insert(ret, head);
            head = tmp;
        }
        ret = reverse(ret);
        return ret;
    }
};
