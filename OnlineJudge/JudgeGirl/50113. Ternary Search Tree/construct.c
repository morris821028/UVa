#include "construct.h"
#include <string.h>

static Node* insert(Node *u, int x) {
	if (u == NULL)	 {
		Node *p = (Node *) calloc(1, sizeof(Node));
		p->small = -1, p->large = x;
		return p;
	}
	if (u->small < 0) {
		if (x < u->large) {
			u->small = x;
		} else {
			u->small = u->large;
			u->large = x;
		}
		return u;
	}
	if (x < u->small)
		u->left = insert(u->left, x);
	else if (x > u->large)
		u->right = insert(u->right, x);
	else
		u->mid = insert(u->mid, x);
	return u;
}
Node* ConstructTree(int A[], int n) {
	Node *ret = NULL;
	for (int i = 0; i < n; i++)
		ret = insert(ret, A[i]);
	return ret;
}
