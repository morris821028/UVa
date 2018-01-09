#include <stdio.h>
#include "operations.h"
 
void printTree(Node *root) {
  if (root == NULL) {
    printf("NULL\n");
    return;
  }
  printf("%d\n", root->n);
  if (root->left == NULL && root->right == NULL) return;
  printTree(root->left);
  printTree(root->right);
}
 
int main() {
  Node node[9];
 
  for(int i = 0; i < 9; i++){
    node[i].n = i;
    node[i].left = node[i].right = NULL;
  }
 
  node[0].left = &node[1];
  node[0].right = &node[2];
  node[1].left = &node[3];
  node[1].right = &node[4];
  node[2].left = &node[5];
  node[2].right = &node[6];
  node[4].left = &node[7];
  node[6].right = &node[8];
 
  Node *tree = FlipTree(&node[0]);
  printTree(&node[0]);
  printTree(tree);
 
  return 0;
}
