#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
	ListNode *next;
	ListNode(int x = 0) : val(x), next(NULL) {}
};
void print(ListNode *head) {
	while (head) {
		printf("%d->", head->val);
		head = head->next;
	} 
	puts("");
}
class Solution {
public:
	ListNode* reverseList(ListNode *st, ListNode *ed) {
		ListNode *curr, *prev, *next;
		ListNode *head = ed;
		curr = st, prev = NULL;
		while (true) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			if (curr == ed)
				break;
			curr = next;
		}
		return head;
	}
    ListNode* reverseKGroup(ListNode* head, int k) {
    	if (head == NULL || k == 1)
    		return head;
    		
        ListNode *left, *right;
        ListNode tmp(-1);
        ListNode *rhead = &tmp, *prev = &tmp;
        int cnt = 0;
        left = head, right = head;
        rhead->next = head;
        while (right != NULL) {
        	cnt++;
        	if (cnt == k) {
        		ListNode *next = right->next;
        		prev->next = reverseList(left, right);
        		prev = left, prev->next = next;
        		left = next, right = next;
        		cnt = 0;
        	} else {
        		right = right->next;
        	}
        }
        
        return rhead->next;
    }
};


int main() {
	Solution s;
	// 1 2 3 4 5, k = 2
	ListNode t[5];
	for (int i = 0; i < 5; i++) {
		t[i] = ListNode(i+1);
		if (i+1 < 5)
			t[i].next = &t[i+1];
	}
	print(s.reverseKGroup(&t[0], 6));
	return 0;
}
