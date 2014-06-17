#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int l, m, i, j;
        int dp[101][101] = {}, used[101][101] = {};
        for(i = 0; i < n; i++)
            scanf("%d %d", &l, &m), used[l][m]++;
        for(i = 1; i <= 100; i++) {
            for(j = 1; j <= 100; j++) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                dp[i][j] += used[i][j];
            }
        }
        printf("%d\n", dp[100][100]);
    }
    puts("*");
    return 0;
}
