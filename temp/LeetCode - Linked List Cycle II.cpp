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
    ListNode *detectCycle(ListNode *head) {
		ListNode *p, *q;
		p = nextNode(head), q = nextNode(p);
		while (p && q && p != q) {
			p = nextNode(p);
			q = nextNode(q), q = nextNode(q);
		}
		if (q == NULL)	return NULL;
		for (q = head; q != p; q = nextNode(q))
			p = nextNode(p);
		return p;
    }
};
/*
faster pointer & slower pointer,

Assume slower pointer use m steps before enter cycle, and cycle length is n,
slower pointer use x steps (in cycle) meet faster pointer,
now, for faster pointer, it make (2(m + x) - m) % n = x %n

=> m + 2 x = i * n + x => m + x = i * n => get (m + x) % n = 0 (at cycle begin first)
=> now, slower pointer has use x steps in cycle. 

	After using m steps to sat. (m+x)%n = 0, it will be at cycle begin first.
*/
int main() {
	return 0;
}
