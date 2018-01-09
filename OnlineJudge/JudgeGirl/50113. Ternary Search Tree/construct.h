typedef struct node{
    int small,large;
    struct node *left,*mid,*right;
} Node;

Node*ConstructTree(int sequence[],int N);
