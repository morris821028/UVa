#include <stdio.h>
#include <string.h>
int main() {
    int f[367][805] = {}, d[367][10];
    int i, j;
    memset(d, 0, sizeof(d));
    f[0][0] = 1, d[0][1] = 1;
    for(i = 1; i <= 366; i++) {
        for(j = 0; j < 800; j++) {
            f[i][j] += f[i-1][j]*i;
            f[i][j+1] += f[i][j]/10;
            f[i][j] %= 10;
        }
        j = 800;
        while(!f[i][j]) j--;
        for(; j >= 0; j--) {
            d[i][f[i][j]]++;
        }
    }
    int n;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d! --\n", n);
        for(i = 0; i < 5; i++) {
            if(i)
                printf("    ");
            else
                printf("   ");
            printf("(%d)%5d", i, d[n][i]);
        }
        puts("");
        for(i = 5; i < 10; i++) {
            if(i != 5)
                printf("    ");
            else
                printf("   ");
            printf("(%d)%5d", i, d[n][i]);
        }
        puts("");
    }
    return 0;
}
