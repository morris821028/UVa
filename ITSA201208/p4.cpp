#include <stdio.h>
#include <stdlib.h>

int main() {
    long long p[50][50] = {};
    int i, j;
    p[0][0] = 1;
    for(i = 1; i < 50; i++) {
        p[i][0] = 1;
        for(j = 1; j <= i; j++)
            p[i][j] = p[i-1][j] + p[i-1][j-1];
    }
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%lld\n", p[n][6]);
        printf("%lld\n", p[n][6]*50);
        printf("%.2llf%%\n", (double)p[n][6]*100/p[49][6]);
    }
    return 0;
}
