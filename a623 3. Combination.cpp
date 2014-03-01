#include <stdio.h>

int main() {
    long long p[100][100] = {};
    int i, j;
    p[0][0] = 1;
    for(i = 1; i < 100; i++) {
        p[i][0] = 1;
        for(j = 1; j <= i; j++)
            p[i][j] = p[i-1][j] + p[i-1][j-1];
    }
    while(scanf("%d %d", &i, &j) == 2)
        printf("%lld\n", p[i][j]);
    return 0;
}
