#include <stdio.h>
#include "construct.h"
 
#define MAXN 1024
char name[MAXN][16];
int height[MAXN];
int weight[MAXN];
 
void PrintBSTree( Node *root ){
    if (root == NULL)
        return;
    printf("%s\n", root->name);
    PrintBSTree(root->left);
    PrintBSTree(root->right);
    return;
}
 
int main(){
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%s %d %d", name[i], &height[i], &weight[i]);
 
    Node *tree = ConstructBSTree( N, name, height, weight );
 
    PrintBSTree( tree );
    return 0;
}
