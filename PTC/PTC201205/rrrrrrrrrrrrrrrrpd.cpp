#include <stdio.h>
#include <queue>
using namespace std;

char pascal[10001][10001] = {};
int main() {
    pascal[0][0] = 1;
    int i, j;
    for(i = 1; i <= 10000; i++) {
        pascal[i][0] = 1;
        for(j = 1; j <= i; j++) {
            pascal[i][j] = pascal[i-1][j-1]+pascal[i-1][j];
            pascal[i][j] %= 2;
        }

    }
    int t, D, K;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &D, &K);
        if(K >= D) {
            if(D == 1) {
                puts("LUCKY!");
                continue;
            }
            puts("UNLUCKY!");
        } else {
            int flag = 0, i, j, k;
            j = D-1;
            for(i = D-2, k = 0; i >= K; i--, k++) {
                flag += pascal[j][k];
                //printf("%d %d¡@%d\n", j, k, pascal[j][k]);
            }
            if(flag&1)
                puts("LUCKY!");
            else
                puts("UNLUCKY!");
        }
    }
    return 0;
}
