#include <stdio.h>
#include <algorithm>
using namespace std;
int dp[45][45][45][45];
int main() {
    int n, m, i, j, k, l;
    int A[1024], x;
    scanf("%d %d", &n, &m);
    for(i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    int b[5] = {};
    for(i = 0; i < m; i++)
        scanf("%d", &x), b[x]++;
    dp[0][0][0][0] = A[1];
    for(i = 0; i <= b[1]; i++)
    for(j = 0; j <= b[2]; j++)
    for(k = 0; k <= b[3]; k++)
    for(l = 0; l <= b[4]; l++) {
        int idx = 1+i+2*j+3*k+4*l;
        if(i >= 1)
            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i-1][j][k][l]+A[idx]);
        if(j >= 1)
            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j-1][k][l]+A[idx]);
        if(k >= 1)
            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k-1][l]+A[idx]);
        if(l >= 1)
            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l-1]+A[idx]);
    }
    printf("%d\n", dp[b[1]][b[2]][b[3]][b[4]]);
    return 0;
}
