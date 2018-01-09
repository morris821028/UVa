#include <stdio.h>
#include "operations.h"
 
int main() {
  Node tree1[9];
 
  for(int i = 0; i < 9; i++){
    tree1[i].n = i;
    tree1[i].left = tree1[i].right = NULL;
  }
 
  tree1[0].left = &tree1[1];
  tree1[0].right = &tree1[2];
  tree1[1].left = &tree1[3];
  tree1[1].right = &tree1[4];
  tree1[2].left = &tree1[5];
  tree1[2].right = &tree1[8];
  tree1[4].left = &tree1[6];
  tree1[6].right = &tree1[7];
 
  depthAvg(&tree1[0]);
 
  return 0;
}
