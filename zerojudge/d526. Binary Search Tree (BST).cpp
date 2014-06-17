#include<stdio.h>
#include<stdlib.h>
struct node {
	int v;
	struct node *lc, *rc;
}*root, *curr, *temp;
void Print(node *now) {
	printf("%d ", now->v);
	if(now->lc != NULL)	Print(now->lc);
	if(now->rc != NULL)	Print(now->rc);
	free(now);
}
main() {
	int n, m, a;
	while(scanf("%d", &n) == 1) {
		scanf("%d", &m);
		temp = (struct node*)malloc(sizeof(struct node));
		temp->v = m, temp->lc = temp->rc = NULL;
		root = temp;
		for(a = 1; a < n; a++) {
			scanf("%d", &m);
			curr = root;
			while(1) {
				if(curr->v > m) {
					if(curr->lc == NULL) {
						temp = (struct node*)malloc(sizeof(struct node));
						temp->v = m, temp->lc = temp->rc = NULL;
						curr->lc = temp; break;
					}	
					else
						curr = curr->lc;
				}
				else if(curr->v < m) {
					if(curr->rc == NULL) {
						temp = (struct node*)malloc(sizeof(struct node));
						temp->v = m, temp->lc = temp->rc = NULL;
						curr->rc = temp; break;
					}
					else
						curr = curr->rc;
				}
				else
					break;
			}
		}
		Print(root), puts("");
	}
	return 0;	
}
