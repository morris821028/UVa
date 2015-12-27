#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "node.h"

typedef struct bstExtra {
	bstNode *parent;
	int val, key;
} bstExtra;
bstNode* bstNode_getLson(bstNode *self) {
	return self->lson;
} 
bstNode* bstNode_getRson(bstNode *self) {
	return self->rson;
}
void bstNode_setLson(bstNode *self, bstNode *u) {
	self->lson = u;
} 
void bstNode_setRson(bstNode *self, bstNode *u) {
	self->rson = u;
}
void bstNode_print(bstNode *self) {
	printf("%d ", ((bstExtra *)(self->extra))->key);
}


int bstNode_init(bstNode *obj) {
	obj->getLson = bstNode_getLson;
	obj->getRson = bstNode_getRson;
	obj->setLson = bstNode_setLson;
	obj->setRson = bstNode_setRson;
	obj->print = bstNode_print;
	obj->extra = (void *) malloc(sizeof(bstExtra));
	return 1;
}
void bstNode_destroy(bstNode *obj) {
	free(obj->extra);
}

Object bstNodeProto = {
    .init = bstNode_init,
    .destroy = bstNode_destroy
};
static void insertCartesianTree(bstNode *p, bstNode *u) {
    while (((bstExtra *)(p->extra))->val 
			> ((bstExtra *)(u->extra))->val) {
        p = ((bstExtra *)p->extra)->parent;
    }
    if (p->rson != NULL)
        ((bstExtra *)(p->rson->extra))->parent = u;
    u->lson = p->rson;
    p->rson = u;
    ((bstExtra *)(u->extra))->parent = p;
}
static int cmp(const bstNode* *x, const bstNode* *y) {
	return ((bstExtra*)(*(bstNode**)x)->extra)->key - ((bstExtra*)(*(bstNode**)y)->extra)->key;
}
bstNode* buildBST(int A[], int n) {
	bstNode *root = NEW(bstNode), *prev;
	bstNode **B = (bstNode**) malloc(sizeof(bstNode*) * n);
	((bstExtra *)(root->extra))->val = INT_MIN;
	prev = root;
	for (int i = 0; i < n; i++) {
		bstNode *curr = NEW(bstNode);
		((bstExtra *)(curr->extra))->key = A[i];
		((bstExtra *)(curr->extra))->val = i;
		B[i] = curr;
	}
	qsort(B, n, sizeof(bstNode*), cmp);
	for (int i = 0; i < n; i++) {
		bstNode *curr = B[i];
		
		insertCartesianTree(prev, curr);
		prev = curr;
	}
	free(B);
	return root->rson;
}
