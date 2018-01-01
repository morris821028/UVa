typedef struct node{
    int value;
    struct node*left;
    struct node*right;
}Node;
Node* ConstructTree(int sequence[],int N);
