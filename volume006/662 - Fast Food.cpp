#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int best[205][205], argbest[205][205];
int dp[35][205], argdp[35][205];
void print(int m, int r) {
    if(m == 0)
        return;
    print(m-1, argdp[m][r]-1);
    printf("Depot %d at restaurant %d serves restaurant", m, argbest[argdp[m][r]][r]);
    if(argdp[m][r] == r)
        printf(" %d\n", r);
    else
        printf("s %d to %d\n", argdp[m][r], r);
}
int main() {
    int n, m, d[205];
    int i, j, k, cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)    break;
        for(i = 1; i <= n; i++)
            scanf("%d", &d[i]);
        for(i = 0; i < n; i++) {
            for(j = 1; j+i <= n; j++) {
                if(i == 0) {
                    best[j][j+i] = 0;
                    argbest[j][j+i] = j;
                } else if(i == 1) {
                    best[j][j+i] = d[j+i]-d[j];
                    argbest[j][j+i] = j;
                } else {
                    best[j][j+i] = best[j+1][j+i-1];
                    best[j][j+i] += abs(d[j]-d[j+i/2])+abs(d[j+i]-d[j+i/2]);
                    argbest[j][j+i] = (j+j+i)/2;
                }
            }
        }
        for(i = 1; i <= n; i++)
            dp[1][i] = best[1][i], argdp[1][i] = 1;
        for(i = 2; i <= m; i++) {
            for(j = i; j <= n; j++) {
                dp[i][j] = 0xfffffff;
                for(k = i-1; k < j; k++) {
                    if(dp[i][j] > dp[i-1][k]+best[k+1][j]) {
                        dp[i][j] = dp[i-1][k]+best[k+1][j];
                        argdp[i][j] = k+1;
                    }
                }
            }
        }
        printf("Chain %d\n", ++cases);
        print(m, n);
        printf("Total distance sum = %d\n", dp[m][n]);
        puts("");
    }
    return 0;
}
