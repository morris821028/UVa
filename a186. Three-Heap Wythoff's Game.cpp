#include <stdio.h>
char dp[201][201][201] = {};
void update(int a, int b, int c) {
    int i, j;
    if(a > c)   i = a, a = c, c = i;
    if(b > c)   i = b, b = c, c = i;
    if(a > b)   i = a, a = b, b = i;
    if(c > 200)    return;
    dp[a][b][c] = 1;
}
int main() {
    int i, j, k, a;
    int cnt = 0;
    for(i = 0; i <= 200; i++)
        for(j = i; j <= 200; j++)
            for(k = j; k <= 200; k++)
                if(!dp[i][j][k]) {
                    printf("%d %d %d\n", i, j, k);
                    for(a = 1; a <= 200; a++) {
                        update(i+a, j, k);
                        update(i, j+a, k);
                        update(i, j, k+a);
                        update(i+a, j+a, k);
                        update(i+a, j, k+a);
                        update(i, j+a, k+a);
                        update(i+a, j+a, k+a);
                    }
                }
    return 0;
}
