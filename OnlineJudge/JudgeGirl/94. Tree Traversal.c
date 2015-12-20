#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

typedef struct TreeNode {
	struct TreeNode *left, *right;
} TreeNode;
typedef struct DataNode {
	int sum;
	TreeNode node;
} DataNode;

#define node_entry(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

DataNode nodes[4096];
int nodesize = 0;
char exp[4096], *eptr;
int peek() {
	while (isspace(*eptr))
        eptr++;
    return eptr[0];
}
void fetch(char c) {
	assert(peek() == c);
    eptr++; 
}
DataNode* newNode() {
	DataNode *p = &nodes[nodesize++];
	p->sum = 0, p->node.left = p->node.right = NULL;
	return p;
}
DataNode* parser() {
	char c = peek();
	DataNode *L, *R, *H = newNode();
	if (c == '(') {
		fetch('(');
		L = parser();
		fetch(',');
		R = parser();
		fetch(')');
		H->node.left = &L->node, H->node.right = &R->node;
		H->sum = L->sum + R->sum;
	} else {
		int ret;
		sscanf(eptr, "%d", &ret);
        while (isdigit(*eptr) || *eptr == '.' || *eptr == '-')
            eptr++;
        H->sum = ret;
	}
	return H;
}
void traversal(TreeNode *nodeptr, int flip) {
	if (nodeptr == NULL)	return ;
	DataNode *d = node_entry(nodeptr, DataNode, node);
	if (!flip) {
		printf("%d\n", d->sum);
		traversal(nodeptr->left, !flip);
		printf("%d\n", d->sum);
		traversal(nodeptr->right, !flip);
	} else {
		printf("%d\n", d->sum);
		traversal(nodeptr->right, !flip);
		printf("%d\n", d->sum);
		traversal(nodeptr->left, !flip);
	}
}
int main() {
	while (scanf("%s", exp) == 1) {
		nodesize = 0;
		eptr = exp;
		DataNode *root = parser();
		traversal(&(root->node), 0);
	}
	return 0;
}
