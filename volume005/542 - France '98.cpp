#include <stdio.h>
#include <stdlib.h>
int p[16][16];
double dp[50][16] = {};
void build(int k, int l, int r) {
    if(l == r) {
        dp[k][l] = 1;
        return;
    }
    int m = (l+r)/2;
    build(k<<1, l, m);
    build(k<<1|1, m+1, r);
    int i, j;
    for(i = l; i <= m; i++) {
        for(j = m+1; j <= r; j++) {
            dp[k][i] += dp[k<<1][i]*dp[k<<1|1][j]*p[i][j]/100;
            dp[k][j] += dp[k<<1][i]*dp[k<<1|1][j]*p[j][i]/100;
        }
    }
}
int main() {
    char name[16][100];
    int i, j;
    for(i = 0; i < 16; i++)
        scanf("%s", name[i]);
    for(i = 0; i < 16; i++)
        for(j = 0; j < 16; j++)
            scanf("%d", &p[i][j]);
    build(1, 0, 15);
    for(i = 0; i < 16; i++)
        printf("%-10s p=%.2lf%%\n", name[i], dp[1][i]*100);
    return 0;
}
