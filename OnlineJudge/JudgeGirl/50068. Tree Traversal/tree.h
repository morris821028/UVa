#ifndef _TREE_H
#define _TREE_H
 
typedef struct Node {
    int label;
    struct Node *left, *right;
} Node;
 
void traversal(Node *root, int N, int command[]);
 
 
#endif
