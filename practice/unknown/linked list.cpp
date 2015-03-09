#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef struct link {
	int key, y; /*key x^y*/
	struct link *next;
}list;
/**/
main() {
	list *head = NULL;
	list *curr = NULL;
	list *newnode;
	list *temp, *pre;
	int x, y;
	
	head = (list *)malloc(sizeof(list));
	head->key = head->y = 0;
	head->next = NULL;
	
	while(scanf("%d %d",&x, &y)==2) {
		curr = head, pre = head;
		while(curr != NULL && curr->y < y)
			pre = curr, curr = curr->next;
		if(curr != NULL && curr->y == y) curr->key += x; 
		else {
			newnode = (list *)malloc(sizeof(list));
			newnode->next = pre->next;
			pre->next = newnode;
			
			newnode->key = x, newnode->y = y;
		}
	}
	curr = head;
	while(curr != NULL)	{
		if(curr->key)
			printf(" %d x^%d ",curr->key, curr->y);
		temp = curr;
		curr = curr->next;
		free (temp);
	}
	system("pause");nline
	return 0;
}
/*
32 100
-7 2
1 6
3 0
*/
inline
