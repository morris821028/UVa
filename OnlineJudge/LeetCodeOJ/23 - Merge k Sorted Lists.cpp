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
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head, *curr;
        priority_queue< pair<int, ListNode*>, vector< pair<int, ListNode*> >, greater< pair<int, ListNode*> > > pQ;
        
        for (int i = 0; i < lists.size(); i++) {
        	if (lists[i] != NULL) {
        		pQ.push(make_pair(lists[i]->val, lists[i]));
        	}
        }
        
        while (!pQ.empty()) {
        	ListNode *u;
        	u = pQ.top().second, pQ.pop();
        	
        	if (u->next != NULL)
        		pQ.push(make_pair(u->next->val, u->next));
        	
        	if (head == NULL)
        		head = u, curr = head;
        	else
        		curr->next = u, curr = curr->next;
        }
        
        return head;
    }
};

int main() {
	Solution s;
	return 0;
}
