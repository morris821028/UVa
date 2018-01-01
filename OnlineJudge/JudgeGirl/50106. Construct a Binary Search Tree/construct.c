#include "construct.h"
#include <stdio.h>
static Node* newNode(char s[], int h, int w) {
	Node *p = calloc(1, sizeof(Node));
	strcpy(p->name, s), p->height = h, p->weight = w;
	return p;
}
static int cmp(Node *u, int h, int w) {
#ifdef HEIGHT
	return h - u->height;
#else
	return w - u->weight;
#endif
}
static Node* insert(Node *u, char s[], int h, int w) {
	if (u == NULL)
		return newNode(s, h, w);
	if (cmp(u, h, w) < 0)
		u->left = insert(u->left, s, h, w);
	else
		u->right = insert(u->right, s, h, w);
	return u;
}
Node* ConstructBSTree(int n, char name[][16], int h[], int w[]) {
	Node *root = NULL;
	for (int i = 0; i < n; i++)
		root = insert(root, name[i], h[i], w[i]);
	return root;
}
