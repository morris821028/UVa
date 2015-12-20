#include <stdio.h>
#include "node.h"

struct node *getNode(struct node *head, unsigned int i) {
	int n = 0;
	struct node *tmp = head;
	
    while (tmp) 
		tmp = tmp->next, n++;
    i = n - 1 - i;
    while (i--) {
    	if (head == NULL)
			return NULL;
		head = head->next;
    }
    return head;
}
