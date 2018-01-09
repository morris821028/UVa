#include <stdio.h>
#include "construct.h"
#define MAXN 32768
int sequence[MAXN];
void PrintTree( Node *root ){
    if (root == NULL)
        return;
    printf("%d %d\n", root->small, root->large);
    PrintTree(root->left);
    PrintTree(root->mid);
    PrintTree(root->right);
    return;
}
int main(){
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%d", &sequence[i]);
    Node *tree = ConstructTree( sequence, N );
    PrintTree( tree );
    return 0;
}
