#ifndef _NODE_H
#define _NODE_H

#include "object.h"

#define NodeMembers(TYPE) \
	Object proto; \
	int (*init)(struct TYPE*); \
	void (*destroy)(struct TYPE*); \
	struct TYPE* (*getLson)(struct TYPE*); \
	struct TYPE* (*getRson)(struct TYPE*); \
	void (*setLson)(struct TYPE*, struct TYPE*); \
	void (*setRson)(struct TYPE*, struct TYPE*); \
	struct TYPE *lson, *rson; \
	void (*print)(struct TYPE*)

typedef struct bNode {
	NodeMembers(bNode);
} bNode;

typedef struct bstNode {
	NodeMembers(bstNode);
	void *extra;
} bstNode;

bstNode* buildBST(int A[], int n);

extern Object bNodeProto;
extern Object bstNodeProto;
#endif
