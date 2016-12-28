#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 1024
void traversal(Node *root, int n, int cmd[]) {
	static Node *stk[MAXN];
	int stkIdx = -1;
	Node *u = root, *p;
	stk[++stkIdx] = u;
	for (int i = 0; i < n; i++) {
		u = stk[stkIdx];
		switch(cmd[i]) {
			case 0:
				printf("%d\n", u->label);
				return ;
			case 1:
				printf("%d\n", u->label);
				break;
			case 2:
				if (stkIdx == 0)
					goto Error;
				--stkIdx;
				break;
			case 3:
				if (u->left == NULL)
					goto Error;
				u = u->left;
				stk[++stkIdx] = u;
				break;			
			case 4:
				if (u->right == NULL)
					goto Error;
				u = u->right;
				stk[++stkIdx] = u;
				break;
			case 5:
				if (stkIdx == 0)
					goto Error;
				p = stk[stkIdx-1];
				if (p->left == NULL || p->right == NULL)
					goto Error;
				if (u == p->left)
					u = p->right;
				else
					u = p->left;
				stk[stkIdx] = u;
		}
	}
	return ;
	Error:
		printf("%d\n", u->label);
}
