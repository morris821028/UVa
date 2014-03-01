#include <stdio.h>

int main() {
    int P;
    int O[5][5];
    int i, j, k;
    while(scanf("%d", &P) == 1) {
        for(i = 0; i < 5; i++)
            for(j = 0; j < 5; j++)
                scanf("%d", &O[i][j]);
        P--;
        while(P--) {
            int x;
            k = 0;
            for(i = 0; i < 5; i++) {
                for(j = 0; j < 5; j++) {
                    scanf("%d", &x);
                    if(x == 1 && O[i][j] == 1)
                        k++;
                    else if(x == 1 && O[i][j] == 8)
                        k += 2;
                    else if(x == 8 && O[i][j] == 1)
                        k += 7;
                    else
                        k += 5;
                    O[i][j] = x;
                }
            }
            printf("%d\n", k);
        }
    }
    return 0;
}
