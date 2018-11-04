#include <stdio.h>
#include "findLength.h"
#define MAXN 256
int main () {
    int array[MAXN][MAXN];
    int N, r, c;
    int direction[4][2] = {{1,0}, {1,1}, {0,1}, {-1,1}};
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &array[i][j]);
    scanf("%d%d", &r, &c);
    for (int i = 0; i < 4; i++)
        printf("%d\n", findLength(array, N, r, c, direction[i][0], direction[i][1]));
    return 0;
}
