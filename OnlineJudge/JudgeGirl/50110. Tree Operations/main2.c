#include <stdio.h>
#include "operations.h"
 
int main() {
  Node tree1[9];
  Node tree2[9];
 
  for(int i = 0; i < 9; i++){
    tree1[i].n = tree2[i].n = i;
    tree1[i].left = tree1[i].right = NULL;
    tree2[i].left = tree2[i].right = NULL;
  }
 
  tree1[0].left = &tree1[1];
  tree1[0].right = &tree1[2];
  tree1[1].left = &tree1[3];
  tree1[1].right = &tree1[4];
  tree1[2].left = &tree1[5];
  tree1[2].right = &tree1[6];
  tree1[4].left = &tree1[7];
  tree1[6].right = &tree1[8];
 
  tree2[0].left = &tree2[1];
  tree2[0].right = &tree2[2];
  tree2[1].left = &tree2[3];
  tree2[1].right = &tree2[4];
  tree2[2].left = &tree2[5];
  tree2[2].right = &tree2[8];
  tree2[4].left = &tree2[6];
  tree2[6].right = &tree2[7];
 
  printf("%d\n", isIdentical(&tree1[0], &tree2[0]));
  printf("%d\n", isIdentical(&tree1[0], &tree1[0]));
  return 0;
}
