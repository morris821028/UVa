#include "node.h"
#include <stdio.h>

bNode* bNode_getLson(bNode *self) {
	return self->lson;
} 
bNode* bNode_getRson(bNode *self) {
	return self->rson;
} 
void bNode_print(bNode *self) {
	printf("%p L %p R %p\n", self, self->lson, self->rson);
}
void bNode_setLson(bNode *self, bNode *u) {
	self->lson = u;
}
void bNode_setRson(bNode *self, bNode *u) {
	self->rson = u;
} 

int bNode_init(bNode *self) {
	self->getLson = bNode_getLson;
	self->getRson = bNode_getRson;
	self->setLson = bNode_setLson;
	self->setRson = bNode_setRson;
	self->print = bNode_print;
	self->lson = NULL, self->rson = NULL;
	return 1;
}
void bNode_destroy(bNode *obj) {
}

Object bNodeProto = {
    .init = bNode_init,
    .destroy = bNode_destroy
};
