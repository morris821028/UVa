#include <stdio.h>
#include "posneg.h" 
int main() {
  int i, j;
  int array[5][5];
  int result[2];
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      scanf("%d", &array[i][j]);
 
  posneg(array, result);
  printf("%d\n", result[0]);
  printf("%d\n", result[1]);
  return 0;
}
