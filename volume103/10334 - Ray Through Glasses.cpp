#include <stdio.h>
#include <stdlib.h>
int f[1001][301] = {};
int main() {
    int i, j;
    f[0][0] = 1, f[1][0] = 2;
    for(i = 2; i <= 1000; i++) {
        for(j = 0; j < 300; j++) {
            f[i][j] = f[i-1][j] + f[i-2][j];
        }
        for(j = 0; j < 300; j++) {
            f[i][j+1] += f[i][j]/10;
            f[i][j] %= 10;
        }
    }
    while(scanf("%d", &i) == 1) {
        j = 299;
        while(f[i][j] == 0) j--;
        while(j >= 0)
            putchar(f[i][j]+'0'), j--;
        puts("");
    }
    return 0;
}
