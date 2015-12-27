#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

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
	printf("%d ", *(int *)(self->extra));
}

int bstNode_init(bstNode *obj) {
	obj->getLson = bstNode_getLson;
	obj->getRson = bstNode_getRson;
	obj->setLson = bstNode_setLson;
	obj->setRson = bstNode_setRson;
	obj->print = bstNode_print;
	obj->extra = (void *) malloc(sizeof(int));
	return 1;
}
void bstNode_destroy(bstNode *obj) {
	free(obj->extra);
}

Object bstNodeProto = {
    .init = bstNode_init,
    .destroy = bstNode_destroy
};
bstNode* buildBST(int A[], int n) {
	bstNode *root = NULL;
	for (int i = 0; i < n; i++) {
		if (root == NULL) {
			root = NEW(bstNode);
			((int*) (root->extra))[0] = A[i];
			continue;
		}
		bstNode *u = root, *v = NEW(bstNode);
		((int*) (v->extra))[0] = A[i];
		while (u != NULL) {
			int x = ((int*) (u->extra))[0];
			if (A[i] < x) {
				if (u->lson == NULL) {
					u->lson = v;
					break;
				}
				u = u->lson;
			} else {
				if (u->rson == NULL) {
					u->rson = v;
					break;
				}
				u = u->rson;
			}
		}
	}
	return root;
}
