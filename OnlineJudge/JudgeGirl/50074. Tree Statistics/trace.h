#ifndef _TRACE_H
#define _TRACE_H

struct ChildList;
struct Node;
typedef struct ChildList ChildList;
typedef struct Node Node;

struct Node {
	ChildList* list;
};
struct ChildList{
	Node* node;
	ChildList* next;
};
typedef struct Answer {
	int InternalNode;
	int Leaf;
	int MaxBranchFactor;
	int Depth;
} Answer;

void trace(Node *root, Answer *ans);

#endif
