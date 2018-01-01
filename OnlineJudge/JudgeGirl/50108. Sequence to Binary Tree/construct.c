#include "construct.h"
#include <stdlib.h>
#define MAXN 32768
static int B[MAXN];

static Node* newNode(int val) {
    Node *p = (Node*) calloc(1, sizeof(Node));
    p->value = val;
    return p;
}
static int cmp(const void *x, const void *y) {
	return *((int *) y) - *((int *) x);
}
Node *ConstructTree(int A[], int n) {
	if (n == 0)
		return NULL;
	if (n < MAXLENGTH) {
		Node *ret = newNode(A[n-1]), *p;
		p = ret;
		for (int i = n-2; i >= 0; i--)
			p->left = newNode(A[i]), p = p->left;
		return ret;
	}
	memcpy(B, A, sizeof(A[0])*n);
	qsort(B, n, sizeof(A[0]), cmp);
	int val = B[MAXLENGTH-1], pos = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] == val) {
			pos = i;
			break;
		}
	}
	Node *ret = newNode(val);
	ret->left = ConstructTree(A, pos);
	ret->right = ConstructTree(A+pos+1, n-pos-1);
	return ret;
}
