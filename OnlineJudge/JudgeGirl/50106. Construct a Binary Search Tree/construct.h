#ifndef CONSTRUCT
#define CONSTRUCT
typedef struct Node{
    char name[16];
    int height;
    int weight;
    struct Node *left, *right;
} Node;
 
Node *ConstructBSTree(int N, char name[][16], int height[], int weight[]);
#endif
