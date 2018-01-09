#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
 
Node* FlipTree(Node *u) {
	if (u == NULL)
		return NULL;
	Node *ret = malloc(sizeof(Node));
	ret->n = u->n;
	ret->left = FlipTree(u->right);
	ret->right = FlipTree(u->left);
	return ret;
}
int isIdentical(Node *t1, Node *t2) {
	if (t1 == NULL && t2 == NULL)
		return 1;
	if (t1 == NULL || t2 == NULL)
		return 0;
	if (t1->n != t2->n)
		return 0;
	return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right);
}
static int dfs(Node *u, int dep, int *sum) {
	if (u == NULL)
		return 0;
	if (u->left == NULL && u->right == NULL) {
		*sum += dep;
		return 1;
	}
	return dfs(u->left, dep+1, sum) + dfs(u->right, dep+1, sum);
}
void depthAvg(Node *root) {
	int sum = 0, cnt;
	cnt = dfs(root, 0, &sum);
	printf("%d/%d\n", sum, cnt);
}
