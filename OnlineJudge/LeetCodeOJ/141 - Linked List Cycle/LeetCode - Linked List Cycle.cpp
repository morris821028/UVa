#include <bits/stdc++.h>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode *nextNode(ListNode *p) {
		return p == NULL ? NULL : p->next;
	}
    bool hasCycle(ListNode *head) {
        ListNode *p, *q;
		p = nextNode(head), q = nextNode(p);
		while (p && q) {
			if (p == q)	
				return true;
			p = nextNode(p);
			q = nextNode(q), q = nextNode(q);
		}
		return false;
    }
};
int main() {
	return 0;
}
