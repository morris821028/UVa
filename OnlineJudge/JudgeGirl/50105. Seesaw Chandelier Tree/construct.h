#ifndef CONSTRUCT
#define CONSTRUCT
typedef struct Node{
    int value;
    struct Node *left, *right;
} Node;
 
Node *ConstructTree(int T[], int N);
#endif
