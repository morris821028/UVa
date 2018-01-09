#ifndef OPERATION
#define OPERATION
typedef struct Node{
    int n;
    struct Node *left, *right;
} Node;
 
Node *FlipTree(Node *root);
int isIdentical(Node *tree1, Node *tree2);
void depthAvg(Node *root);
#endif
